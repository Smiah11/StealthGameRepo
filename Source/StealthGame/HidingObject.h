// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "HidingObject.generated.h"


UCLASS()
class STEALTHGAME_API AHidingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHidingObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HideBox")
		UBoxComponent* BoxCollision;


protected:


public:	

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
