// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "RTSGameMode.h"

#include "UI/UserUI.h"
#include "UI/PauseMenu.h"

FRTSGameMode::FRTSGameMode(FWindow* InWindow, FRTSGameEngine* CustomGameEngine)
	: Window(InWindow)
	, GameEngine(CustomGameEngine)
{
	UserUIPtr = FAutoDeletePointer(new FUserUI());
	PauseMenuPtr = FAutoDeletePointer(new FPauseMenu(Window, CustomGameEngine));
}

void FRTSGameMode::StartGame()
{
	UserUIPtr->InitializeUI();
}

void FRTSGameMode::EndGame()
{
	UserUIPtr->DeInitializeUI();
}

void FRTSGameMode::StartEditor()
{
}

void FRTSGameMode::EndEditor()
{
}
