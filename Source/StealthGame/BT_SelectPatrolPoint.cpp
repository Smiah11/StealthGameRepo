// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_SelectPatrolPoint.h"
#include "StealthGame.h"
#include "AIPatrolPoint.h"
#include "AIPatrollerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTask.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AAIPatrollerController* AICon = Cast<AAIPatrollerController>(OwnerComp.GetAIOwner());

	if (AICon)//check if cast is succesful
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();// gets the blackboard component of the AI controller

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("MoveTo"));// gets the current patrol point

		TArray<AActor*>AvailablePatrolPoints = AICon->GetPatrolPoints();// gets the array of all patrol points

		int32 RandomNumber = FMath::RandRange(0, AvailablePatrolPoints.Num() - 1);//Allows the AI to go through Patrol Points at Random


		AActor*NextPatrolPoint = AvailablePatrolPoints[RandomNumber]; // chooses Patrol Point at random (makes it easier to have multiple AI in the map)
		

		BlackboardComp->SetValueAsObject("MoveTo",NextPatrolPoint);// sets the blackboard value of MoveTo to the next patrol point

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
