#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/RenderComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "UI/GameUserUI.h"

class FRTSGameMode;

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UBaseTransformComponent>("TransformComponent");

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImageSize({ 64, 64 });
}

void EUnitFactoryBase::BeginPlay()
{
	EEntity::BeginPlay();

	const FAssetCollectionItem& Asset = GetFactoryAsset();
	RenderComponent->SetImage(Asset.GetAssetName(), Asset.GetAssetPath());

	RegisterToScreenSelection(GetEntityManagerOwner());
}

FVector2D<int> EUnitFactoryBase::GetLocation()
{
	if (TransformComponent != nullptr)
	{
		return TransformComponent->GetLocation();
	}

	return { };
}

FVector2D<int> EUnitFactoryBase::GetSize()
{
	if (RenderComponent != nullptr)
	{
		return TransformComponent->GetSize();
	}

	return { };
}

void EUnitFactoryBase::OnSelect()
{
	LOG_DEBUG("FactoryBase selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr)
	{
		FGameUserUI* UserUI = RTSGameMode->GetUserUI();
		if (UserUI != nullptr)
		{
			UserUI->AddFactoryBase(this);
		}
	}
}

void EUnitFactoryBase::OnDeSelect()
{
	LOG_DEBUG("FactoryBase de-selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr)
	{
		FGameUserUI* UserUI = RTSGameMode->GetUserUI();
		if (UserUI != nullptr)
		{
			UserUI->RemoveFactoryBase(this);
		}
	}
}

FAssetCollectionItem EUnitFactoryBase::GetFactoryAsset()
{
	return RTSAssetCollection::FactoryBase;
}
