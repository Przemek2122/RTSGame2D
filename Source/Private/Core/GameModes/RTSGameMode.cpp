// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "ECS/UnitFactoryBase.h"
#include "ECS/Entities/CameraManager.h"
#include "Engine/Logic/GameModeManager.h"

FRTSGameMode::FRTSGameMode(FGameModeManager* InGameModeManager)
	: FGameModeBase(InGameModeManager)
{
	FWindowAdvanced* WindowAdvanced = InGameModeManager->GetOwnerWindowAdvanced();

	UserUIPtr = FAutoUIMenu(new FGameUserUI(WindowAdvanced));
	PauseMenuPtr = FAutoUIMenu(new FGamePauseMenu(WindowAdvanced));
}

void FRTSGameMode::Initialize()
{
	FGameModeBase::Initialize();

	PauseMenuPtr->InitializePublic();

	FWindowAdvanced* WindowAdvanced = GetWindowAdvanced();
	if (WindowAdvanced != nullptr)
	{
		WindowAdvanced->GetEntityManager()->CreateEntity<EUnitFactoryBase>("FactoryBase1");
	}
}

void FRTSGameMode::Start()
{
	UserUIPtr->InitializePublic();
}

void FRTSGameMode::End()
{
}
