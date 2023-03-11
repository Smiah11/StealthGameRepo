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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHidingObject::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AHidingObject::OnOverlapEnd);


}


//function that checks that the other actor is not null and is not itself, and allows player to be hidden
void AHidingObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		OtherActor->SetActorHiddenInGame(true);
	}
}

void AHidingObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		OtherActor->SetActorHiddenInGame(false);
	}

}

