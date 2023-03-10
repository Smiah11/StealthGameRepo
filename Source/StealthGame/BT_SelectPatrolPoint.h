// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTask.h"
#include "BT_SelectPatrolPoint.generated.h"



UCLASS()
class STEALTHGAME_API UBTSelectPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

		/* perform the task logic*/
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	
};
