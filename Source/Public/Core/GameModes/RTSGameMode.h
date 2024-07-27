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
	void Initialize() override;

	void Start() override;
	void End() override;
	/** End of FGameModeBase */

	FGameUserUI* GetUserUI() const { return UserUIPtr.Get(); }

private:
	FPlayerState* CreatePlayerState(const FUserId& InUserId) override;

private:
	/** User UI - There should be factory placing, units, and more */
	FAutoUIMenu<FGameUserUI> UserUIPtr;

	/** Pause menu - IN-GAME only */
	FAutoUIMenu<FGamePauseMenu> PauseMenuPtr;
	
};
