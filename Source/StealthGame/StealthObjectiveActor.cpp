// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStealthObjectiveActor::AStealthObjectiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void AStealthObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStealthObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);//calls the base implemenation

	SpawnEffects();
}

