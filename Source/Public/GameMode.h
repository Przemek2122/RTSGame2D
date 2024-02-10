// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"

class FRTSGameEngine;
class FPauseMenu;
class FUserUI;

class FGameMode
{
public:
	FGameMode(FWindow* InWindow, FRTSGameEngine* CustomGameEngine);

	/** Called when game should be started */
	void StartGame();
	/** Called when game should be ended */
	void EndGame();

protected:
	/** Pointer to owner window */
	FWindow* Window;
	/** Pointer to game engine */
	FRTSGameEngine* GameEngine;
	/** User UI - There should be factory placing, units, and more */
	FAutoDeletePointer<FUserUI> UserUIPtr;
	/** Pause menu - IN-GAME only */
	FAutoDeletePointer<FPauseMenu> PauseMenuPtr;
	
};
