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

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Blackboard")
        FBlackboardKeySelector BlackboardKey;

    FName GetSelectedBlackboardKey() const;
};
