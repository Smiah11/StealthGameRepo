// Fill out your copyright notice in the Description page of Project Settings.


#include "BTClearValue.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include <BehaviorTree/Tasks/BTTask_BlackboardBase.h>
#include "AIPatrollerController.h"


UBTClearValue::UBTClearValue()
{
    NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UBTClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        // Get the key that needs to be cleared
        FName KeyName = GetSelectedBlackboardKey();

        // Clear the value in the blackboard
        BlackboardComp->ClearValue(KeyName);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

FName UBTClearValue::GetSelectedBlackboardKey() const
{
    return BlackboardKey.SelectedKeyName;
}

