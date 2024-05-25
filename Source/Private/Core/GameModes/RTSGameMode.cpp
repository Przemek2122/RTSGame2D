// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "ECS/MyScreenSelectionEntity.h"
#include "ECS/UnitBase.h"
#include "ECS/UnitFactoryBase.h"
#include "ECS/Collision/CollisionManager.h"
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
	Super::Initialize();

	PauseMenuPtr->InitializePublic();
}

void FRTSGameMode::Start()
{
	UserUIPtr->InitializePublic();

	FWindowAdvanced* WindowAdvanced = GetWindowAdvanced();
	if (WindowAdvanced != nullptr)
	{
		FMap* CurrentMap = WindowAdvanced->GetMapManager()->GetCurrentMap();
		if (CurrentMap != nullptr)
		{
			FCollisionManager* CollisionManager = CurrentMap->CreateSubSystem<FCollisionManager>();

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

			/*
			CArray<EUnitBase*> NewEntities = EntityManager->CreateMultipleEntities<EUnitBase>(100);
			for (EUnitBase* NewEntity : NewEntities)
			{
				FVector2D<int> NewLocation = { FMath::RandRange(64, 512), FMath::RandRange(64, 512) };

				UBaseTransformComponent* TransformComponent = dynamic_cast<UBaseTransformComponent*>(NewEntity->GetRootComponent());
				if (TransformComponent != nullptr)
				{
					TransformComponent->SetLocationUser(NewLocation);
				}
			}
			*/
		}
	}
}

void FRTSGameMode::End()
{
	LOG_INFO("RTSGameMode ended.");
}
