// Created by Przemys�aw Wiewi�ra 2023

#pragma once

#include "CoreMinimal.h"

class FPauseMenu;
class FUserUI;

class FGameMode
{
public:
	FGameMode(FWindow* InWindow);

	/** Called when game should be started */
	void StartGame();
	/** Called when game should be ended */
	void EndGame();

protected:
	/** Pointer to owner window */
	FWindow* Window;
	/** User UI - There should be factory placing, units, and more */
	FAutoDeletePointer<FUserUI> UserUIPtr;
	FAutoDeletePointer<FPauseMenu> PauseMenuPtr;
	
};
