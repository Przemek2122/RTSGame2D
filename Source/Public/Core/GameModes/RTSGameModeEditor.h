// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"

/**
 * Game mode used in map editor.
 */
class FRTSGameModeEditor : public FGameModeBase
{
public:
	FRTSGameModeEditor(FGameModeManager* InGameModeManager);

	void Initialize() override;
	void DeInitialize() override;



};
