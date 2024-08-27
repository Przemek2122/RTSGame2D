#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "Core/RTSAssetCollection.h"
#include "Core/RTSHUD.h"
#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/Collision/CircleCollisionComponent.h"
#include "ECS/Components/Collision/CollisionComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TargetingComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "UI/GameUserUI.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EInteractableEntityBase(InEntityManager)
{
	TransformComponent = CreateComponent<UParentComponent>("TransformComponent");

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");

	RenderComponent->SetImageSize({ 32, 32 });

	HealthComponent = TransformComponent->CreateComponent<UHealthComponent>("HealthComponent");
	MoveComponent = TransformComponent->CreateComponent<UMoveComponent>("MoveComponent");
	TargetingComponent = TransformComponent->CreateComponent<UTargetingComponent>("TargetingComponent");

	CollisionComponent = TransformComponent->CreateComponent<UCircleCollisionComponent>("CollisionComponent");
}

void EUnitBase::BeginPlay()
{
	Super::BeginPlay();

	const FAssetCollectionItem& Asset = GetUnitAsset();
	RenderComponent->SetImage(Asset.GetAssetName(), Asset.GetAssetPath());
}

FVector2D<int> EUnitBase::GetLocation()
{
	if (TransformComponent != nullptr)
	{
		return TransformComponent->GetLocation();
	}

	return { };
}

FVector2D<int> EUnitBase::GetSize()
{
	if (RenderComponent != nullptr)
	{
		return TransformComponent->GetSize();
	}

	return { };
}

void EUnitBase::OnSelect()
{
	LOG_DEBUG("UnitBase selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr && RTSGameMode->GetLocalController())
	{
		ERTSHUD* HUD = RTSGameMode->GetLocalController()->GetHUD<ERTSHUD>();
		if (HUD != nullptr)
		{
			FGameUserUI* UserUI = HUD->GetUserUI();
			if (UserUI != nullptr)
			{
				UserUI->AddUnitBase(this);
			}
		}
	}
}

void EUnitBase::OnDeSelect()
{
	LOG_DEBUG("UnitBase de-selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr && RTSGameMode->GetLocalController())
	{
		ERTSHUD* HUD = RTSGameMode->GetLocalController()->GetHUD<ERTSHUD>();
		if (HUD != nullptr)
		{
			FGameUserUI* UserUI = HUD->GetUserUI();
			if (UserUI != nullptr)
			{
				UserUI->RemoveUnitBase(this);
			}
		}
	}
}

void EUnitBase::OnDoAction(const FVector2D<int>& ActionLocation)
{
	Super::OnDoAction(ActionLocation);

	LOG_INFO("EUnitBase::OnDoAction@" << ActionLocation);

	MoveComponent->SetTargetMoveLocation(ActionLocation);
}

const FAssetCollectionItem& EUnitBase::GetUnitAsset()
{
	return RTSAssetCollection::UnitBase;
}
