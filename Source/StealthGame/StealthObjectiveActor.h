// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthObjectiveActor.generated.h"

class USphereComponent;//reduces compilation time since the include is not in the header file

UCLASS()
class STEALTHGAME_API AStealthObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStealthObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* MeshComp;


	UPROPERTY(VisibleAnywhere,Category = Components)
	USphereComponent* SphereComp;


	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* PickupFX;


	void SpawnEffects();//Plays Particle effect on overlap

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
