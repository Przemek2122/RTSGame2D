#include "GamePCH.h"
#include "Core/GameModes/RTSGameModeEditor.h"

FRTSGameModeEditor::FRTSGameModeEditor(FGameModeManager* InGameModeManager)
	: FGameModeBase(InGameModeManager)
{
	PauseMenu = FAutoUIMenu<FEditorPauseMenu>(GetWindowAdvanced());
	UserUI = FAutoUIMenu<FEditorUserUI>(GetWindowAdvanced());
}

void FRTSGameModeEditor::Initialize()
{
	FGameModeBase::Initialize();

	PauseMenu->InitializePublic();
}

void FRTSGameModeEditor::DeInitialize()
{
	FGameModeBase::DeInitialize();
}

void FRTSGameModeEditor::Start()
{
	FGameModeBase::Start();

	UserUI->InitializePublic();
}
