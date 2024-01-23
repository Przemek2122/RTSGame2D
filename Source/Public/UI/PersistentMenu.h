#pragma once

#include "CoreMinimal.h"

class FTextWidget;

class FPersistentMenu
{
public:
	FPersistentMenu(FWindow* InGameWindow);

	void Initialize();

	FTextWidget* GetFPSTextWidget() const;

protected:
	FWindow* GameWindow;
	FTextWidget* TextFPSWidget;
};
