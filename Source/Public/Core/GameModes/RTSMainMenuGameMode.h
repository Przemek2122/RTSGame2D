// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"
#include "UI/MainMenu.h"

/**
 * Game mode used in map editor.
 */
class FRTSMainMenuGameMode : public FGameModeBase
{
public:
	FRTSMainMenuGameMode(FGameModeManager* InGameModeManager);

	/** Begin FGameModeBase */
	void Initialize() override;
	void Start() override;
	/** End FGameModeBase */

protected:
	FAutoUIMenu<FMainMenu> MainMenuPtr;

};
