#include "GamePCH.h"
#include "UI/EditorPauseMenu.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"

FEditorPauseMenu::FEditorPauseMenu(FWindowAdvanced* InOwnerWindow)
	: FPauseUIMenu(InOwnerWindow)
{
}

void FEditorPauseMenu::OnExitToMenu(FWindowAdvanced* WindowAdvanced)
{
	FPauseUIMenu::OnExitToMenu(WindowAdvanced);

	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	MapManager->DeactivateCurrentGameMap();
	MapManager->UnloadAllMaps();

	DisablePauseMenu();

	WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
}
