// Created by Przemysław Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#include "GamePCH.h"
#include "Core/ShooterGameEngine.h"

#include "GameMode.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/MainMenu.h"
#include "UI/PersistentMenu.h"

FShooterGameEngine::FShooterGameEngine() = default;

void FShooterGameEngine::Init()
{
	LOG_DEBUG("Game init");

	GameWindow = GEngine->GetEngineRender()->CreateWindow<FWindow>(TEXT_CHAR("Game window"), 200, 200, 800, 600);
	if (GameWindow != nullptr)
	{
		GameModePtr = FAutoDeletePointer<FGameMode>(GameWindow);
		PersistentMenuPtr = FAutoDeletePointer<FPersistentMenu>(GameWindow);
		MainMenuPtr = FAutoDeletePointer<FMainMenu>(GameWindow, GameModePtr.Get());

		PersistentMenuPtr->Initialize();
		MainMenuPtr->Initialize();
	}
}

void FShooterGameEngine::PostSecondTick()
{
	if (PersistentMenuPtr.HasAnyObject())
	{
		PersistentMenuPtr.Get()->GetFPSTextWidget()->SetText(std::to_string(GetFramesThisSecond()));
	}
}
