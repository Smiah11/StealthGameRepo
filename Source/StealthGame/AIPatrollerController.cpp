// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrollerController.h"
#include "StealthGame.h"
#include "AIPatroller.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "DistractionProjectile.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


AAIPatrollerController::AAIPatrollerController()
{
	// Initialise Blackboard and Behaviour Tree
	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));


	// initalise Blackboard Keys
	MoveToKey = "MoveTo";
	MoveToPlayerKey = "Player Location";
	MoveToSoundKey = "Sound Location";
	ReturnToObjectiveKey = "Return";

	CurrentPatrolPoint = 0;

}

void AAIPatrollerController::PlayerCaught(APawn* const pawn)
{
	
	if (BlackboardComp)
	{
		
		BlackboardComp->SetValueAsObject(MoveToPlayerKey, pawn);
	}
}
void AAIPatrollerController::SoundHeard(const FVector& Location)
{

	AAIPatrollerController* AIController = this;
	UBlackboardComponent* BlackboardComponent = AIController ? AIController->FindComponentByClass<UBlackboardComponent>() : nullptr;

	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsVector(MoveToSoundKey, Location);
		
	}

	// Move the AI to the noise location using the AI Move To task node
	if (AIController)
	{
		AIController->MoveToLocation(Location);
		
	}
}


void AAIPatrollerController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	AAIPatroller* AICharacter = Cast<AAIPatroller>(pawn); // Reference to Character

	// Check if Cast is Successful

	if (AICharacter)
	{
		if (AICharacter->BehaviourTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviourTree->BlackboardAsset)); //IF IS NOT NULL blackboard is then initalised
		}

		//populate Patrol Point Array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviourComp->StartTree(*AICharacter->BehaviourTree);
		
	}
}



