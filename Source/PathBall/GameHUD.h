// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PATHBALL_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextWinner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool win;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool pause;

private:

	UPROPERTY(EditAnywhere, Category = "MatchUI")
	TSubclassOf<class UUserWidget> HUDMatchWidgetClass;

	UPROPERTY(EditAnywhere, Category = "MatchUI")
	TSubclassOf<class UUserWidget> HUDMenuWidgetClass;

	UPROPERTY(EditAnywhere, Category = "MatchUI")
	TSubclassOf<class UUserWidget> HUDPauseWidgetClass;

	UPROPERTY(EditAnywhere, Category = "MatchUI")
	class UUserWidget* CurrentWidget;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CheckPause();
};
