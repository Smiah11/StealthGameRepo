// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatroller.h"
#include "StealthGame.h"
#include "AIPatrollerController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <DrawDebugHelpers.h>
#include <Perception/AIPerceptionComponent.h>
#include "StealthGameMode.h"


// Sets default values
AAIPatroller::AAIPatroller()
{
	//initalise Pawn Senses
	PawnSenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSenseComp"));
	PawnSenseComp->SetPeripheralVisionAngle(30.f);//sets AI Vision
	PawnSenseComp->HearingThreshold = 600.f; //sets AI Hearing
	PawnSenseComp->LOSHearingThreshold = 600.f; //sets AI LOS Hearing
	

}


// Called when the game starts or when spawned
void AAIPatroller::BeginPlay()
{
	Super::BeginPlay();


	// Call the On Player Caught Function if the AI sees the player
	if (PawnSenseComp)
	{
		
		PawnSenseComp->OnHearNoise.AddDynamic(this, &AAIPatroller::OnNoiseHeard); //calls the On Noise Heard Function if the AI hears the player
		PawnSenseComp->OnSeePawn.AddDynamic(this, &AAIPatroller::OnPlayerCaught); //calls the On Player Caught Function if the AI sees the player
		
	}
	
}

// Called to bind functionality to input
void AAIPatroller::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}



void AAIPatroller::OnNoiseHeard(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	AAIPatrollerController* AIController = Cast<AAIPatrollerController>(GetController()); // gets reference to player controller

	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Sound has been heard"));
		DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Cyan, false, 10.0f);
		DrawDebugString(GetWorld(), Location, "Distracted", nullptr, FColor::Cyan, 0.5f, true);
		GetCharacterMovement()-> MaxWalkSpeed = 350.f;
		AIController->SoundHeard(Location);
		
	}
}
void AAIPatroller::OnPlayerCaught(APawn* Pawn)
{
	AAIPatrollerController* AIController = Cast<AAIPatrollerController>(GetController()); // gets reference to player controller
	
	if (AIController)
	{
	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("You've been caught"));
		DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 32.0f, 12, FColor::Purple, false, 10.0f);
		GetCharacterMovement()-> MaxWalkSpeed = 700.f;
		AIController->PlayerCaught(Pawn);

		AStealthGameMode* GM = Cast<AStealthGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(Pawn, false);
		}
	
	}

}


