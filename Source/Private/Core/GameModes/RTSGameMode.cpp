// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "ECS/MyScreenSelectionEntity.h"
#include "ECS/UnitBase.h"
#include "ECS/UnitFactoryBase.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

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

	const FWindowAdvanced* WindowAdvanced = GetWindowAdvanced();
	if (WindowAdvanced != nullptr)
	{
		const FMap* CurrentMap = WindowAdvanced->GetMapManager()->GetCurrentMap();
		if (CurrentMap != nullptr)
		{
			FEntityManager* EntityManager = CurrentMap->GetEntityManager();

			// Should be moved to system - In Entity Component System scheme - But system does not exists yet
			EntityManager->CreateEntity<EMyScreenSelectionEntity>();

			// Create sample factory
			EntityManager->CreateEntityAt<EUnitFactoryBase>({ 64, 64 });

			// Create sample units
			EntityManager->CreateEntityAt<EUnitBase>({ 128, 128 });
			EntityManager->CreateEntityAt<EUnitBase>({ 128, 256 });
			EntityManager->CreateEntityAt<EUnitBase>({ 256, 256 });
			EntityManager->CreateEntityAt<EUnitBase>({ 256, 128 });
		}
	}
}

void FRTSGameMode::End()
{
	LOG_INFO("RTSGameMode ended.");
}
