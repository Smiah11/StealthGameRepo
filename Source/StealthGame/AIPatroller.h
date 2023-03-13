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

	/* allows the ai to use senses*/
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSenseComp; 

	/* function to return the main menu level*/
	void ReturnToMainMenu();

	/*timer handle to return to the menu*/
	FTimerHandle TimerHandle;

	


	// Call this function to set the noise location
private:
	/*Function for when player is seen/caught*/
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	/*Function for when a noise is heard whether it be footsteps or a distraction*/
	UFUNCTION()
		void OnNoiseHeard(APawn* PawnInstigator, const FVector& Location, float Volume);

	
	/* FVector to for the noice location*/
	FVector NoiseLocation;



};

