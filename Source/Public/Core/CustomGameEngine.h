// Created by Przemys³aw Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "UI/MainMenu.h"
#include "UI/PersistentMenu.h"

class FWindowAdvanced;
class FRTSGameMode;
class FTextWidget;

class FRTSGameEngine : public FEngine
{
	friend FEngineManager;

protected:
	FRTSGameEngine();

public:
	/** Begin FEngine */
	void Init() override;
	void PostSecondTick() override;
	/** End FEngine */

	//FMainMenu* GetMainMenu() const { return MainMenuPtr.Get(); }
	FWindowAdvanced* GetGameWindowAdvanced() const { return GameWindowAdvanced; }

protected:
	/** Game window, lifecycle managed by engine */
	FWindowAdvanced* GameWindowAdvanced;

	FAutoUIMenu<FPersistentMenu> PersistentMenuPtr;

};

