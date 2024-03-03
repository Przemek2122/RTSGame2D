// Created by Przemysław Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#include "GamePCH.h"
#include "Core/CustomGameEngine.h"

#include "RTSGameMode.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/MainMenu.h"
#include "UI/PersistentMenu.h"

FRTSGameEngine::FRTSGameEngine()
	: GameWindow(nullptr)
{
}

void FRTSGameEngine::Init()
{
	LOG_DEBUG("Game init");

	GameWindow = GEngine->GetEngineRender()->CreateWindow<FWindow>(TEXT_CHAR("Game window"), 200, 200, 800, 600);
	if (GameWindow != nullptr)
	{
		GameModePtr = FAutoDeletePointer<FRTSGameMode>(GameWindow, this);
		PersistentMenuPtr = FAutoDeletePointer<FPersistentMenu>(GameWindow);
		MainMenuPtr = FAutoDeletePointer<FMainMenu>(GameWindow, GameModePtr.Get());

		PersistentMenuPtr->Initialize();
		MainMenuPtr->Initialize();
	}
}

void FRTSGameEngine::PostSecondTick()
{
	if (PersistentMenuPtr.HasAnyObject())
	{
		PersistentMenuPtr.Get()->GetFPSTextWidget()->SetText(std::to_string(GetFramesThisSecond()));
	}
}
