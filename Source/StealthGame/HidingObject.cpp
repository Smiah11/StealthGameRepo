// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingObject.h"

// Sets default values
AHidingObject::AHidingObject()
{
	
	//creates a box collision component and sets it as the root component

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = BoxCollision;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHidingObject::OnOverlapBegin);//binds the function to the overlap begin event
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AHidingObject::OnOverlapEnd);//binds the function to the overlap end event


}


//function that checks that the other actor is not null and is not itself, and allows player to be hidden
void AHidingObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You are hidden"));//debug text to show the actor is hidden
		OtherActor->SetActorHiddenInGame(true);//sets actor to be hidden
	}
}
//function that allows the player upon exiting the object to be visible again
void AHidingObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("You are no longer hidden"));//debug text to show the actor is no visible again
		OtherActor->SetActorHiddenInGame(false);//sets actor to be visible again
	}

}

