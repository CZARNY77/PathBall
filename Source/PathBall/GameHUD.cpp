// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

AGameHUD::AGameHUD() 
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MatchUI(TEXT("/Game/HUD/MatchUI"));
	HUDMatchWidgetClass = MatchUI.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuUI(TEXT("/Game/HUD/Menu/MenuUI"));
	HUDMenuWidgetClass = MenuUI.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseUI(TEXT("/Game/HUD/PauseUI"));
	HUDPauseWidgetClass = PauseUI.Class;

	win = false;
	pause = false;
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetWorld()->GetName());

	if (GetWorld()->GetName() == "Menu"){
		if (HUDMenuWidgetClass) {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDMenuWidgetClass);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Menu")));
			if (CurrentWidget)	CurrentWidget->AddToViewport();
		}
	}
	else {
		if (HUDMatchWidgetClass) {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDMatchWidgetClass);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Win")));
			if (CurrentWidget)	CurrentWidget->AddToViewport();


		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	
}

void AGameHUD::CheckPause()
{
	if (HUDPauseWidgetClass) {

		if (pause) {
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDPauseWidgetClass);
			CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDMatchWidgetClass);
		}

		if (CurrentWidget) {
			//CurrentWidget->RemoveFromViewport();
			CurrentWidget->AddToViewport();
		}
	}

}
