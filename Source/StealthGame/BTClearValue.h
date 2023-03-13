// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BTClearValue.generated.h"


UCLASS()
class STEALTHGAME_API  UBTClearValue : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTClearValue();
    /* creates a task node with my own custom task */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    /* Select the blackboard key that needs to be cleared */
    UPROPERTY(EditAnywhere, Category = "Blackboard")
        FBlackboardKeySelector BlackboardKey;

    /* Gets the blackboard key that has been selected*/
    FName GetSelectedBlackboardKey() const;
};
