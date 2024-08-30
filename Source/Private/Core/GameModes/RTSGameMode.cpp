// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "Core/RTSPlayerController.h"
#include "ECS/BulletProjectileEntity.h"
#include "ECS/MyScreenSelectionEntity.h"
#include "ECS/UnitBase.h"
#include "ECS/UnitFactoryBase.h"
#include "ECS/Collision/CollisionManager.h"
#include "ECS/Components/TeamComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

FRTSGameMode::FRTSGameMode(FGameModeManager* InGameModeManager)
	: FGameModeBase(InGameModeManager)
{
}

void FRTSGameMode::Start()
{
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

			auto CreateFactoryLambda = [&](const FVector2D<int32> Location)
			{
				EUnitFactoryBase* Factory = EntityManager->CreateEntityAt<EUnitFactoryBase>(Location);
				Factory->GetTeamComponent()->SetOwnerUserId(GetLocalUserId());
			};

			auto CreateUnitLambda = [&](const FVector2D<int32> Location)
			{
				EUnitBase* Unit = EntityManager->CreateEntityAt<EUnitBase>(Location);
				Unit->GetTeamComponent()->SetOwnerUserId(GetLocalUserId());
			};

			// Create sample factory
			CreateFactoryLambda({ 64, 64 });

			// Create sample units
			CreateUnitLambda({ 154, 128 });
			CreateUnitLambda({ 128, 256 });
			CreateUnitLambda({ 256, 256 });
			CreateUnitLambda({ 256, 128 });

			EBulletProjectileEntity* ProjectileEntity = EntityManager->CreateEntityAt<EBulletProjectileEntity>({ 256, 256 });
			ProjectileEntity->SetProjectileMovementParams(EProjectileMovementParams(120.f, 95));

#if _DEBUG
			constexpr bool bPerformanceTestEnabled = false;
			constexpr int32 NumberOfEntities = 128;

			if (bPerformanceTestEnabled)
			{
				CArray<EUnitBase*> NewEntities = EntityManager->CreateMultipleEntities<EUnitBase>(NumberOfEntities);
				for (EUnitBase* NewEntity : NewEntities)
				{
					FVector2D<int> NewLocation = { FMath::RandRange(64, 512), FMath::RandRange(64, 512) };

					// ...
				}
			}
#endif
		}
	}
}

void FRTSGameMode::End()
{
	LOG_INFO("RTSGameMode ended.");
}

void FRTSGameMode::SetDefaultControllers()
{
	Super::SetDefaultControllers();

	// Add AI user
	FAIController* AIState = AddBot();
}

FPlayerController* FRTSGameMode::CreatePlayerController()
{
	return CreateController<FRTSPlayerController>();
}
