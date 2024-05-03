// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "Core/GameModes/RTSGameMode.h"

#include "ECS/MyScreenSelectionEntity.h"
#include "ECS/UnitBase.h"
#include "ECS/UnitFactoryBase.h"
#include "ECS/Components/BaseTransformComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"
#include "Timer/TimerManager.h"

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

			EUnitFactoryBase* Factory1 = EntityManager->CreateEntity<EUnitFactoryBase>();
			dynamic_cast<UBaseTransformComponent*>(Factory1->GetRootComponent())->SetLocationUser({ 64, 64 });

			EUnitBase* Unit1 = EntityManager->CreateEntity<EUnitBase>();
			dynamic_cast<UBaseTransformComponent*>(Unit1->GetRootComponent())->SetLocationUser({ 128, 128 });
		}
	}

	// TODO Move to test class and add some kind of Long run test class that does not end immediately
	/*
	FDelegateSafe<void, FOptionalTimerParams*> TimerDelegate;
	TimerDelegate.BindLambda([&](FOptionalTimerParams*)
	{
		LOG_INFO("Timer finished.");
		LOG_INFO("Time elapsed since timer start: " << TemporaryTimer->GetTimeElapsedSinceStart());

		TemporaryTimer.reset();
	});

	TemporaryTimer = FTimerManager::CreateTimerAsync(TimerDelegate, 2.f);
	*/

	TemporaryTimer = FTimerManager::CreateTimerAsync([&](FOptionalTimerParams*)
	{
		LOG_INFO("Timer finished.");
		LOG_INFO("Time elapsed since timer start: " << TemporaryTimer->GetTimeElapsedSinceStart());

		//TemporaryTimer.reset();
	}, 2.f);
}

void FRTSGameMode::End()
{
	LOG_INFO("RTSGameMode ended.");
}
