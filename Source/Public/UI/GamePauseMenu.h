#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

class FWindowAdvanced;

class FGamePauseMenu : public FPauseUIMenu
{
public:
	FGamePauseMenu(FWindowAdvanced* InWindowAdvanced);

protected:
	void OnExitToMenu(FWindowAdvanced* WindowAdvanced) override;

};
