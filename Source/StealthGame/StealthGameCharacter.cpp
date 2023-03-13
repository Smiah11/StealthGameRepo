// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include <DrawDebugHelpers.h>
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "DistractionProjectile.h"

//////////////////////////////////////////////////////////////////////////
// AStealthGameCharacter

AStealthGameCharacter::AStealthGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	FireCooldownDuration = 2.0f; // 2 second cooldown
	bIsOnFireCooldown = false;

	

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComp"));

	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStealthGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);//sets up the jump action
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);// sets up the stop jump action

	PlayerInputComponent->BindAxis("MoveForward", this, &AStealthGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStealthGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AStealthGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AStealthGameCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Crouch",  IE_Pressed,this, &AStealthGameCharacter::StartCrouch);//Sets up the Crouch action
	PlayerInputComponent->BindAction("Crouch",  IE_Released, this, &AStealthGameCharacter::StopCrouch);//sets up the stop crouch action
	PlayerInputComponent->BindAction("Distraction", IE_Pressed, this, &AStealthGameCharacter::Fire);//sets up the distraction action

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AStealthGameCharacter::StartSprint);// sets up the sprint action
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AStealthGameCharacter::StopSprint);// sets up the stop sprint action



}

void AStealthGameCharacter::Fire()
{

	if (bIsOnFireCooldown)
	{
		// just checks if currently on cooldown, so they can't fire yet
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You're on a cooldown"));
		return;
		
	}
	
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Distraction Used"));

			FVector SpawnLocation = ACharacter::GetMesh()->GetSocketLocation("Distraction");// Get the Distraction socket location
			FRotator SpawnRotation = ACharacter::GetMesh()->GetSocketRotation("Distraction");// Get the Distraction socket rotation

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;// Specifies the parameters for spawning an actor
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = this;//Specifies the instigator of the actor being spawned


			// spawn the projectile at the SOCKET

			GetWorld()->SpawnActor<ADistractionProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			//DrawDebugSphere(GetWorld(), HandLocation, 50.f, 12, FColor::Red, false, 5.f);
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{

			PlayAnimMontage(FireAnimation);
		}
		// Put the Fire ability on cooldown
		bIsOnFireCooldown = true;
		GetWorldTimerManager().SetTimer(FireCooldownTimerHandle, this, &AStealthGameCharacter::EndFireCooldown, FireCooldownDuration, false);

}

void AStealthGameCharacter::EndFireCooldown()
{
	bIsOnFireCooldown = false;
}

void AStealthGameCharacter::StartCrouch()
{
	//GetCharacterMovement()->MaxWalkSpeed = 300.f;
	Crouch();
}

void AStealthGameCharacter::StopCrouch()
{
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	UnCrouch();
}

void AStealthGameCharacter::ReportNoise(USoundBase* Sound, float Volume)
{
	//If we have a valid sound to play, play the sound and
	//report it to our game
	if (Sound)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("You're making noise"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), Volume);//Play the actual sound

		//Report that we've played a sound with a certain volume in a specific location
		
		MakeNoise(Volume, this, GetActorLocation());
		DrawDebugSphere(GetWorld(), GetActorLocation(), 32.0f, 12, FColor::Orange, false, 10.0f);
		
	}
}

void AStealthGameCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;//sets the sprint speed
	
}
void AStealthGameCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;//sets the speed back to normal after sprinting
	
	
	
}


void AStealthGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AStealthGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AStealthGameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AStealthGameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
