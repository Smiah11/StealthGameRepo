// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "StealthGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStealthObjectiveActor::AStealthObjectiveActor()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);// no collision needed for object
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//no physics needed
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//stops anything from interacting with the object
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//allows player to interact with object
	SphereComp->SetupAttachment(MeshComp);

}

void AStealthObjectiveActor::SpawnEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

// Called when the game starts or when spawned
void AStealthObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnEffects();
	
}


void AStealthObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);//calls the base implemenation

	SpawnEffects();

	AStealthGameCharacter*MyCharacter = Cast<AStealthGameCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();//destroys actor to make it look like its been picked up
	}
}

