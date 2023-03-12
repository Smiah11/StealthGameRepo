// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_MenuController.h"

void AMain_MenuController::BeginPlay()
{
	Super::BeginPlay();
    // Show the mouse cursor and enable input
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    // Set input mode to UI only
    SetInputMode(FInputModeUIOnly());
}
