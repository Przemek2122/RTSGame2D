#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

class FTextWidget;

class FPersistentMenu : public FUIMenu
{
public:
	FPersistentMenu(FWindow* InGameWindow);

	void Initialize();

	FTextWidget* GetFPSTextWidget() const;

protected:
	FTextWidget* TextFPSWidget;
};
