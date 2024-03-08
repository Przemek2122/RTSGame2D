#include "GamePCH.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeManager.h"

FRTSMainMenuGameMode::FRTSMainMenuGameMode(FGameModeManager* InGameModeManager)
	: FGameModeBase(InGameModeManager)
{
	
}

void FRTSMainMenuGameMode::Initialize()
{
	FGameModeBase::Initialize();

	MainMenuPtr = FAutoUIMenu<FMainMenu>(GetOwnerGameModeManager()->GetOwnerWindowAdvanced());
}

void FRTSMainMenuGameMode::Start()
{
	FGameModeBase::Start();

	MainMenuPtr->InitializePublic();
}
