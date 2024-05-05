#include "GamePCH.h"
#include "UI/GamePauseMenu.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"
#include "Timer/Timer.h"

FGamePauseMenu::FGamePauseMenu(FWindowAdvanced* InWindowAdvanced)
	: FPauseUIMenu(InWindowAdvanced)
{
}

void FGamePauseMenu::OnExitToMenu(FWindowAdvanced* WindowAdvanced)
{
	FPauseUIMenu::OnExitToMenu(WindowAdvanced);

	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	MapManager->DeactivateCurrentGameMap();
	MapManager->UnloadAllMaps();

	DisablePauseMenu();

	WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
}

void FGamePauseMenu::OnMenuShown()
{
	FPauseUIMenu::OnMenuShown();

	FTimerCollector::Get()->PauseAllTimers();
}

void FGamePauseMenu::OnMenuHidden()
{
	FPauseUIMenu::OnMenuHidden();

	FTimerCollector::Get()->ResumeAllTimers();
}
