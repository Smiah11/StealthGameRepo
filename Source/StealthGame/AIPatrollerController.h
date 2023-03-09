// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
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

		void OnPossess(APawn* const Pawn) override;




public:

	AAIPatrollerController();

	int32 CurrentPatrolPoint = 0;//Checks which patrol point the AI is currently on

	void PlayerCaught(APawn*Pawn);

	void SoundHeard(FVector Location);

	//inline getter functions

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*>GetPatrolPoints() const { return PatrolPoints; }


};
