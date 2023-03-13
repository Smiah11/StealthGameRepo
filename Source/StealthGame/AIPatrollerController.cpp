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
//updates the blackboard of the AI controller with the location of the player that was caught so that the patroller can move to that location
void AAIPatrollerController::PlayerCaught(APawn* const pawn)
{
	
	if (BlackboardComp)
	{
		
		BlackboardComp->SetValueAsObject(MoveToPlayerKey, pawn);//sets the blackboard value to the location of the player
	}
}
//updates the blackboard of the AI controller with the location of the sound that was heard so that the patroller can move to that location
void AAIPatrollerController::SoundHeard(const FVector& Location)
{

	AAIPatrollerController* AIController = this;
	UBlackboardComponent* BlackboardComponent = AIController ? AIController->FindComponentByClass<UBlackboardComponent>() : nullptr;

	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsVector(MoveToSoundKey, Location);// sets the blackboard value to the location of the sound
		
	}

	if (AIController)
	{
		AIController->MoveToLocation(Location);// Move the AI to the noise location using the AI Move To task node
		
	}
}

//function called when ai is possesed by the AIPatrollerController
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

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);//populate Patrol Point Array

		BehaviourComp->StartTree(*AICharacter->BehaviourTree);//starts the behaviour tree
		
	}
}



