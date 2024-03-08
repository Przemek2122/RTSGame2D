// Created by Przemysław Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#include "GamePCH.h"
#include "Core/CustomGameEngine.h"

#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FRTSGameEngine::FRTSGameEngine()
	: GameWindowAdvanced(nullptr)
{
}

void FRTSGameEngine::Init()
{
	LOG_DEBUG("Game init");

	GameWindowAdvanced = GEngine->GetEngineRender()->CreateWindow<FWindowAdvanced>(TEXT_CHAR("Game window"), 200, 200, 800, 600);
	if (GameWindowAdvanced != nullptr)
	{
		PersistentMenuPtr = FAutoUIMenu<FPersistentMenu>(GameWindowAdvanced);
		PersistentMenuPtr->InitializePublic();

		FRTSMainMenuGameMode* MainMenuGameMode = GameWindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
	}
}

void FRTSGameEngine::PostSecondTick()
{
	if (PersistentMenuPtr.HasAnyObject())
	{
		PersistentMenuPtr.Get()->GetFPSTextWidget()->SetText(std::to_string(GetFramesThisSecond()));
	}
}
