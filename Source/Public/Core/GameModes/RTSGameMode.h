// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"
#include "UI/GameUserUI.h"
#include "UI/GamePauseMenu.h"

class FRTSGameEngine;

/**
 * GameMode used in game.
 */
class FRTSGameMode : public FGameModeBase
{
public:
	FRTSGameMode(FGameModeManager* InGameModeManager);

	/** Called when game should be started */
	void Start() override;
	/** Called when game should be ended */
	void End() override;

protected:
	/** User UI - There should be factory placing, units, and more */
	FAutoUIMenu<FGameUserUI> UserUIPtr;
	/** Pause menu - IN-GAME only */
	FAutoUIMenu<FGamePauseMenu> PauseMenuPtr;
	
};
