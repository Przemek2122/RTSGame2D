// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"
#include "UI/EditorPauseMenu.h"
#include "UI/EditorUserUI.h"

/**
 * Game mode used in map editor.
 */
class FRTSGameModeEditor : public FGameModeBase
{
public:
	FRTSGameModeEditor(FGameModeManager* InGameModeManager);

	/** Begin FGameModeBase */
	void Initialize() override;
	void DeInitialize() override;

	void Start() override;
	/** End FGameModeBase */

protected:
	FAutoUIMenu<FEditorPauseMenu> PauseMenu;
	FAutoUIMenu<FEditorUserUI> UserUI;

};
