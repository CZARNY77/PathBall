// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Path.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PATHBALL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	//void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	AMyPlayerController();

	class APath* LastPath;

protected:

	virtual void PlayerTick(float DeltaTime) override;

	void MoveToMouseCursor();
};
