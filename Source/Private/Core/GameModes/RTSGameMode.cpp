// Created by Przemys�aw Wiewi�ra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "Core/PlayerState.h"
#include "ECS/BulletProjectileEntity.h"
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
			// Add collision subsystem
			CurrentMap->CreateSubSystem<FCollisionManager>();

			FEntityManager* EntityManager = CurrentMap->GetEntityManager();

			// Should be moved to system - In Entity Component System scheme
			EntityManager->CreateEntity<EMyScreenSelectionEntity>();

			// Create sample factory
			EntityManager->CreateEntityAt<EUnitFactoryBase>({ 64, 64 });

			// Create sample units
			EntityManager->CreateEntityAt<EUnitBase>({ 128, 128 });
			EntityManager->CreateEntityAt<EUnitBase>({ 128, 256 });
			EntityManager->CreateEntityAt<EUnitBase>({ 256, 256 });
			EntityManager->CreateEntityAt<EUnitBase>({ 256, 128 });

			EBulletProjectileEntity* ProjectileEntity = EntityManager->CreateEntityAt<EBulletProjectileEntity>({ 256, 256 });
			ProjectileEntity->SetProjectileMovementParams(EProjectileMovementParams(120.f, 95));

			/*
			CArray<EUnitBase*> NewEntities = EntityManager->CreateMultipleEntities<EUnitBase>(100);
			for (EUnitBase* NewEntity : NewEntities)
			{
				FVector2D<int> NewLocation = { FMath::RandRange(64, 512), FMath::RandRange(64, 512) };

				UParentComponent* TransformComponent = dynamic_cast<UParentComponent*>(NewEntity->GetRootComponent());
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

FPlayerState* FRTSGameMode::CreatePlayerState(const FUserId& InUserId)
{
	return new FRTSPlayerState(InUserId);
}
