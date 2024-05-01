#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "Core/RTSAssetCollection.h"
#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TargetingComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "UI/GameUserUI.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UBaseTransformComponent>("TransformComponent");
	TransformComponent->SetLocationFinal({ 140, 151 });

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");

	RenderComponent->SetImageSize({ 32, 32 });

	HealthComponent = TransformComponent->CreateComponent<UHealthComponent>("HealthComponent");
	MoveComponent = TransformComponent->CreateComponent<UMoveComponent>("MoveComponent");
	TargetingComponent = TransformComponent->CreateComponent<UTargetingComponent>("TargetingComponent");
}

void EUnitBase::BeginPlay()
{
	EEntity::BeginPlay();

	const FAssetCollectionItem& Asset = GetUnitAsset();
	RenderComponent->SetImage(Asset.GetAssetName(), Asset.GetAssetPath());

	RegisterToScreenSelection(GetEntityManagerOwner());

	// @TODO Test UMoveComponent - To be deleted
	TransformComponent->SetRotation(90);
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
	if (RTSGameMode != nullptr)
	{
		FGameUserUI* UserUI = RTSGameMode->GetUserUI();
		if (UserUI != nullptr)
		{
			UserUI->AddUnitBase(this);
		}
	}
}

void EUnitBase::OnDeSelect()
{
	LOG_DEBUG("UnitBase de-selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr)
	{
		FGameUserUI* UserUI = RTSGameMode->GetUserUI();
		if (UserUI != nullptr)
		{
			UserUI->RemoveUnitBase(this);
		}
	}
}

const FAssetCollectionItem& EUnitBase::GetUnitAsset()
{
	return RTSAssetCollection::UnitBase;
}
