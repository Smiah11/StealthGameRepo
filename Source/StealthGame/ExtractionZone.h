// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "ExtractionZone.generated.h"


UCLASS()
class STEALTHGAME_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();
	UPROPERTY(VisibleAnywhere, Category = Components)
	UBoxComponent* ExtractionComp;


protected:
	/*handle an overlap event between the player and the extraction zone */
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	

	/*timer handle for the return to main menu*/
	FTimerHandle TimerHandle_MainMenu;
	/*Function that switches the level to the main menu*/
	void ReturntoMainMenu();
};
