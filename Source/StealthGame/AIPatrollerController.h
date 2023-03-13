// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include <Perception/PawnSensingComponent.h>
#include "AIPatrollerController.generated.h"


/**
 * 
 */
UCLASS()
class STEALTHGAME_API AAIPatrollerController : public AAIController
{
	GENERATED_BODY()


		//Behaviour Tree Component
		UBehaviorTreeComponent* BehaviourComp;



		//Blackboard Component

		UBlackboardComponent* BlackboardComp;

		//Blackboard Keys
		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName MoveToKey;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName MoveToPlayerKey;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName MoveToSoundKey;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName ReturnToObjectiveKey;


		// array to store patrol point actors to find the next target point

		TArray<AActor*>PatrolPoints;
		float MaxWalkSpeed = 150.f;

	

		




public:

	AAIPatrollerController();

	/*Checks which patrol point the AI is currently on*/
	int32 CurrentPatrolPoint = 0;

	/*function to update the blackboard with the location of the player caught*/
	void PlayerCaught(APawn*Pawn);

	/*function to update the blackboard with the location of the sound heard*/
	void SoundHeard(const FVector& Location);

	/*function to start behaviour tree once AI is possessed by the assigned controller*/
	void OnPossess(APawn* const Pawn) override;

	/*Bool to check if player has already been caught*/
	bool bPlayerCaught; 

	//inline getter functions

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*>GetPatrolPoints() const { return PatrolPoints; }


};
