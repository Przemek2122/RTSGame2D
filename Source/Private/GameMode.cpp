// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "GameMode.h"

#include "UI/UserUI.h"
#include "UI/PauseMenu.h"

FGameMode::FGameMode(FWindow* InWindow, FRTSGameEngine* CustomGameEngine)
	: Window(InWindow)
	, GameEngine(CustomGameEngine)
{
	UserUIPtr = FAutoDeletePointer(new FUserUI());
	PauseMenuPtr = FAutoDeletePointer(new FPauseMenu(Window, CustomGameEngine));
}

void FGameMode::StartGame()
{
}

void FGameMode::EndGame()
{
}
