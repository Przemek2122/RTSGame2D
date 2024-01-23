// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"

class FUserUI;

class FGameMode
{
public:
	FGameMode(FWindow* InWindow);

	/** Called when user wants to open selection for playing a map */
	void OpenGameMapSelection();
	/** Called when user wants to open selection for playing a map */
	void OpenEditorMapSelection();

	/** Called when game should be started */
	void StartGame();
	/** Called when game should be ended */
	void EndGame();

protected:
	/** Pointer to owner window */
	FWindow* Window;
	/** User UI - There should be factory placing, units, and more */
	FAutoDeletePointer<FUserUI> UserUIPtr;
	
};
