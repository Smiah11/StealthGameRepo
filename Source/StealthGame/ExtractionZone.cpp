// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "StealthGameCharacter.h"
#include "StealthGameMode.h"

// Sets default values
AExtractionZone::AExtractionZone()
{

	ExtractionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtractionComp"));
	ExtractionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExtractionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExtractionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ExtractionComp->SetBoxExtent(FVector(200.0f));
	RootComponent = ExtractionComp;

	ExtractionComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);
}


void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone!"));//log warning for testing

	AStealthGameCharacter*MyChar= Cast<AStealthGameCharacter>(OtherActor);
	if (MyChar&&MyChar->bIsCarryingObjective==true)// checks to see if the player is carrying the objective and if the player is the actual player and not the ai
	{
		AStealthGameMode*GM=Cast<AStealthGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(MyChar,true);// mission success
		}
	}
}


