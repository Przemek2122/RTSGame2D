// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "Core/RTSPlayerController.h"
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

	// Add first user
	FPlayerController* FirstUser = AddPlayer();

	// Add AI user
	FAIController* AIState = AddBot();
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

#if _DEBUG
			constexpr bool bPerformanceTestEnabled = false;
			constexpr int32 NumberOfEntities = 128;

			if (bPerformanceTestEnabled)
			{
				CArray<EUnitBase*> NewEntities = EntityManager->CreateMultipleEntities<EUnitBase>(NumberOfEntities);
				for (EUnitBase* NewEntity : NewEntities)
				{
					FVector2D<int> NewLocation = { FMath::RandRange(64, 512), FMath::RandRange(64, 512) };

					UParentComponent* TransformComponent = dynamic_cast<UParentComponent*>(NewEntity->GetRootComponent());
					if (TransformComponent != nullptr)
					{
						TransformComponent->SetLocation(NewLocation);
					}
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

FPlayerController* FRTSGameMode::CreatePlayerController()
{
	return CreateController<FRTSPlayerController>();
}
