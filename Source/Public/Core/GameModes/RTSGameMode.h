// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/GameModeBase.h"
#include "UI/GameUserUI.h"
#include "UI/GamePauseMenu.h"

/**
 * GameMode used in game.
 */
class FRTSGameMode : public FGameModeBase
{
public:
	FRTSGameMode(FGameModeManager* InGameModeManager);

	/** Begin of FGameModeBase */
	void Initialize() override;

	void Start() override;
	void End() override;
	/** End of FGameModeBase */

	FUserId GetLocalUserId() const;
	const FPlayerController* GetLocalController() const;

protected:
	/** Override player controller class */
	FPlayerController* CreatePlayerController() override;

private:
	/** Local user controller */
	FPlayerController* LocalUserController;
	
};
