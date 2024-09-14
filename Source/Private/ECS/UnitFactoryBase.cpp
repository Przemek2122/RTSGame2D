#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "Core/RTSHUD.h"
#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/Collision/SquareCollisionComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "UI/GameUserUI.h"

FConstructionUnitData::FConstructionUnitData(const std::basic_string<char>& InName, FAssetCollectionItem InAssetCollectionItem)
	: Name(InName)
	, AssetCollectionItem(std::move(InAssetCollectionItem))
{
}

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EInteractableEntityBase(InEntityManager)
{
	TransformComponent = CreateComponent<UParentComponent>("TransformComponent");
	TransformComponent->SetSize({ 64, 64 });

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetRenderLocationType(ERenderType::LeftTopCorner); // Render as square from left top corner instead of default center

	SquareCollisionComponent = TransformComponent->CreateComponent<USquareCollisionComponent>("SquareCollisionComponent");
}

void EUnitFactoryBase::BeginPlay()
{
	Super::BeginPlay();

	const FAssetCollectionItem& Asset = GetFactoryAsset();
	RenderComponent->SetImage(Asset.GetAssetName(), Asset.GetAssetPath());
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
	if (RTSGameMode != nullptr && RTSGameMode->GetLocalController())
	{
		ERTSHUD* HUD = RTSGameMode->GetLocalController()->GetHUD<ERTSHUD>();
		if (HUD != nullptr)
		{
			FGameUserUI* UserUI = HUD->GetUserUI();
			if (UserUI != nullptr)
			{
				UserUI->AddFactory(this);
			}
		}
	}
}

void EUnitFactoryBase::OnDeSelect()
{
	LOG_DEBUG("FactoryBase de-selected");

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
				UserUI->RemoveFactory(this);
			}
		}
	}
}

const FAssetCollectionItem& EUnitFactoryBase::GetFactoryAsset() const
{
	return RTSAssetCollection::FactoryBase;
}

std::string EUnitFactoryBase::GetFactoryName() const
{
	static const std::string BaseFactoryName = "Base factory";

	return BaseFactoryName;
}

CArray<FConstructionUnitData> EUnitFactoryBase::GetUnits() const
{
	CArray<FConstructionUnitData> OutConstructionUnitArray;

	FConstructionUnitData MeleeUnit("Melee unit", RTSAssetCollection::UnitBase);
	FConstructionUnitData RangedUnit("Ranged unit", RTSAssetCollection::UnitBase);

	OutConstructionUnitArray.Push(MeleeUnit);
	OutConstructionUnitArray.Push(RangedUnit);

	return OutConstructionUnitArray;
}

void EUnitFactoryBase::AddUnitToQueue()
{
}

void EUnitFactoryBase::RemoveUnitFromQueue()
{
}
