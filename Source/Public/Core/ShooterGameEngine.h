// Created by Przemys³aw Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

class FPersistentMenu;
class FMainMenu;
class FGameMode;
class FTextWidget;

class FShooterGameEngine : public FEngine
{
	friend FEngineManager;

protected:
	FShooterGameEngine();

public:
	void Init() override;

	void PostSecondTick() override;

protected:
	/** Game window, lifecycle managed by engine */
	FWindow* GameWindow;

	FAutoDeletePointer<FGameMode> GameModePtr;
	FAutoDeletePointer<FPersistentMenu> PersistentMenuPtr;
	FAutoDeletePointer<FMainMenu> MainMenuPtr;

};

