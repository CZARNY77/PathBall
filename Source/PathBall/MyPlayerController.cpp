// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Path.h"

AMyPlayerController::AMyPlayerController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MoveToMouseCursor();
}

void AMyPlayerController::MoveToMouseCursor() // funckja odpowiada za zmiane koloru na ¿ó³ty po najechaniu
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	APath* CurrentPath = Cast<APath>(Hit.GetActor());

	if ((LastPath) && (LastPath != CurrentPath)) LastPath->GetOutOnPath();

	if (CurrentPath) {
		CurrentPath->HoverOnPath();
		LastPath = CurrentPath;
	}
}
