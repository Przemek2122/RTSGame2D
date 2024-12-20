#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

class FWindowAdvanced;

class FGamePauseMenu : public FPauseUIMenu
{
public:
	FGamePauseMenu(FWindow* InWindowAdvanced);

protected:
	void OnExitToMenu(FWindowAdvanced* WindowAdvanced) override;

	void OnMenuShown() override;
	void OnMenuHidden() override;

};
