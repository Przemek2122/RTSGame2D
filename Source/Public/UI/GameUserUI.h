#pragma once

#include "CoreMinimal.h"
#include "Interfaces/CoreLoop/ITickInterface.h"
#include "Renderer/Widgets/UIMenu.h"

class FHorizontalBoxWidget;

class FGameUserUI : public FUIMenu
{
public:
	FGameUserUI(FWindow* InGameWindow);

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

protected:
	FHorizontalBoxWidget* MainHorizontalBox;

};
