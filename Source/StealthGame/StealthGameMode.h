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
	/*Actor used to switch camera viewpoint upon mission fail/success*/
	UPROPERTY(EditDefaultsOnly, Category = "Spectating");
	TSubclassOf<AActor>SpectatingViewpointClass;


public:
	AStealthGameMode();

	/*function that contains the mission complete logic*/
	void CompleteMission(APawn*InstigatorPawn, bool BMissionSuccess);

	/*event for when mission is complete, to access in blueprint*/
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionComplete(APawn* InstigatorPawn, bool BMissionSuccess);
	
};
