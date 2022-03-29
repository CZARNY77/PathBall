// Copyright Epic Games, Inc. All Rights Reserved.


#include "PathBallGameModeBase.h"
#include "MyPlayerController.h"
#include "Gracz.h"
#include "GameHUD.h"

APathBallGameModeBase::APathBallGameModeBase() {

	DefaultPawnClass = AGracz::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}