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

	FWindowCreationData WindowCreationData(false);

	static const std::string WindowName = "Game window";
	static const FVector2D<int> WindowLocation = FVector2D<int>(25, 150);
	static const FVector2D<int> WindowDefaultSize = FVector2D<int>(800, 600);

	GameWindowAdvanced = GEngine->GetEngineRender()->CreateWindow<FWindowAdvanced>(WindowCreationData, WindowName, WindowLocation, WindowDefaultSize);
	if (GameWindowAdvanced != nullptr)
	{
		PersistentMenuPtr = FAutoUIMenu<FPersistentMenu>(GameWindowAdvanced);
		PersistentMenuPtr->InitializePublic();

		GameWindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
#if DEBUG
		GameWindowAdvanced->StartWidgetDebugger();
#endif
	}
}

void FRTSGameEngine::PostSecondTick()
{
	if (PersistentMenuPtr.HasAnyObject())
	{
		const std::string FramesNumText = std::to_string(GetFramesThisSecond());

		PersistentMenuPtr.Get()->GetFPSTextWidget()->SetText(FramesNumText);
	}
}
