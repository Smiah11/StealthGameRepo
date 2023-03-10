// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StealthGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AStealthGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectating");
	TSubclassOf<AActor>SpectatingViewpointClass;


public:
	AStealthGameMode();

	void CompleteMission(APawn*InstigatorPawn, bool BMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionComplete(APawn* InstigatorPawn, bool BMissionSuccess);
	
};
