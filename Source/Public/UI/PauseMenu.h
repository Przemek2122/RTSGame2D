#pragma once

#include "CoreMinimal.h"

class FVerticalBoxWidget;

class FPauseMenu
{
public:
	FPauseMenu(FWindow* InGameWindow);

	/** Generates default menu layout */
	void Initialize();

	void Show();
	void Hide();

protected:
	FWindow* GameWindow;

	FVerticalBoxWidget* VerticalBoxWidget;

};
