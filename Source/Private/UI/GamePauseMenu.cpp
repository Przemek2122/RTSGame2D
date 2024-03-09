#include "GamePCH.h"
#include "UI/GamePauseMenu.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"

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
