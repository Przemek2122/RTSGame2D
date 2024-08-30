// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"
#include "UI/GameUserUI.h"
#include "UI/GamePauseMenu.h"

/**
 * GameMode used in game.
 */
class FRTSGameMode : public FGameModeBase
{
public:
	FRTSGameMode(FGameModeManager* InGameModeManager);

	/** Begin of FGameModeBase */
	void Start() override;
	void End() override;
	/** End of FGameModeBase */

protected:
	void SetDefaultControllers() override;

	/** Override player controller class */
	FPlayerController* CreatePlayerController() override;
	
};
