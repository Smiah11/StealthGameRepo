// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameMode.h"
#include <Kismet/GameplayStatics.h>


AStealthGameMode::AStealthGameMode()
{

}


void AStealthGameMode::CompleteMission(APawn*InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);//disables game character movement

	//switching the camera to a different view upon mission success/failure	
			TArray<AActor*>ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			AActor* ViewTarget = nullptr;

			if (ReturnedActors.Num() > 0)
			{
				ViewTarget = ReturnedActors[0];

				APlayerController* PlayerCon = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PlayerCon)
				{
					PlayerCon->SetViewTargetWithBlend(ViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		

	
	}
	OnMissionComplete(InstigatorPawn,bMissionSuccess);
}
