// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIPatrollerController.h"
#include "AIPatroller.generated.h"


UCLASS()
class STEALTHGAME_API AAIPatroller : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPatroller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviourTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSenseComp; //allows the AI to use sight for player detection


	
	

	// Call this function to set the noise location
private:
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);


	UFUNCTION()
	void OnNoiseHeard(APawn* PawnInstigator, const FVector& Location, float Volume);

	
	FVector NoiseLocation;


	
};

