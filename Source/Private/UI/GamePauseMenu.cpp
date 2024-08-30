#include "GamePCH.h"
#include "UI/GamePauseMenu.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"
#include "Timer/Timer.h"

FGamePauseMenu::FGamePauseMenu(FWindow* InWindowAdvanced)
	: FPauseUIMenu(InWindowAdvanced)
{
}

void FGamePauseMenu::OnExitToMenu(FWindowAdvanced* WindowAdvanced)
{
	DisablePauseMenu();

	Super::OnExitToMenu(WindowAdvanced);

	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	MapManager->DeactivateCurrentGameMap();
	MapManager->UnloadAllMaps();

	WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
}

void FGamePauseMenu::OnMenuShown()
{
	Super::OnMenuShown();

	FTimerCollector::Get()->PauseAllTimers();
}

void FGamePauseMenu::OnMenuHidden()
{
	Super::OnMenuHidden();

	FTimerCollector::Get()->ResumeAllTimers();
}
