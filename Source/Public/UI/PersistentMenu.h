#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

class FTextWidget;

class FPersistentMenu : public FUIMenu
{
public:
	FPersistentMenu(FWindow* InGameWindow);

	FTextWidget* GetFPSTextWidget() const;

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

protected:
	FTextWidget* TextFPSWidget;

};
