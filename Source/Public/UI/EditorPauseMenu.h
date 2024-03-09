#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

class FWindowAdvanced;

class FEditorPauseMenu : public FPauseUIMenu
{
public:
	FEditorPauseMenu(FWindowAdvanced* InOwnerWindow);

protected:
	void OnExitToMenu(FWindowAdvanced* WindowAdvanced) override;

};
