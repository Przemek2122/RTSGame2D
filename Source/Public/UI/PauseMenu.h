#pragma once

#include "CoreMinimal.h"

class FPauseMenu
{
public:
	FPauseMenu(FWindow* InGameWindow);

	void Initialize();

protected:
	FWindow* GameWindow;

};
