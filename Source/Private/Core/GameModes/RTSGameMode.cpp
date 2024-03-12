// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

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
}

void FRTSGameMode::Start()
{
	UserUIPtr->InitializePublic();

	FEntityManager* EntityManager = GetWindowAdvanced()->GetEntityManager();
	if (EntityManager != nullptr)
	{
		EntityManager->CreateEntity<ECameraManager>("CameraManager");
	}
}

void FRTSGameMode::End()
{
}
