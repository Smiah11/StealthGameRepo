// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Main_MenuController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AMain_MenuController : public APlayerController
{
	GENERATED_BODY()
	
		public:
			virtual void BeginPlay() override;
};
