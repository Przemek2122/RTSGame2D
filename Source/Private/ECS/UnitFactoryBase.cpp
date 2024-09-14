#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "Core/RTSHUD.h"
#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/Collision/SquareCollisionComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "Timer/TimerManager.h"
#include "UI/GameUserUI.h"

FVisualUnitData::FVisualUnitData(const std::basic_string<char>& InName, FAssetCollectionItem InAssetCollectionItem)
	: Name(InName)
	, AssetCollectionItem(std::move(InAssetCollectionItem))
{
}
FConstructionUnitData::FConstructionUnitData(FVisualUnitData InVisualUnitData)
	: VisualUnitData(std::move(InVisualUnitData))
	, TimeToBuildUnit(5.0f)
{
}

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EInteractableEntityBase(InEntityManager)
	, FactoryState(EFactoryState::Idle)
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

	CreateUnitList();
}

void EUnitFactoryBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UnitBuildQueue.Size() > 0)
	{
		if (UnitBuildTimer != nullptr && UnitBuildTimer->IsActive())
		{
			const float TimerPercent = UnitBuildTimer->GetTimerPercent();
			LOG_INFO("Percent: " << TimerPercent);
		}
		else if (FactoryState == EFactoryState::Idle || FactoryState == EFactoryState::BuildingUnitFinished)
		{
			FactoryState = EFactoryState::BuildingUnit;

			const FConstructionUnitData& CurrentUnit = UnitBuildQueue[0];

			FDelegateSafe<void, FOptionalTimerParams*> TimerDelegate;
			TimerDelegate.BindObject(this, &EUnitFactoryBase::OnUnitBuildFinish);
			UnitBuildTimer = FTimerManager::CreateTimerSync(TimerDelegate, CurrentUnit.TimeToBuildUnit);
		}
	}
	else if (FactoryState == EFactoryState::BuildingUnitFinished)
	{
		FactoryState = EFactoryState::Idle;
	}
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

const CArray<FVisualUnitData>& EUnitFactoryBase::GetUnits() const
{
	return BuildableUnitsForWidgetArray;
}

void EUnitFactoryBase::AddUnitToQueue(const FVisualUnitData& InVisualUnitDat)
{
	for (const FConstructionUnitData& BuildableUnit : BuildableUnitsArray)
	{
		if (BuildableUnit.VisualUnitData == InVisualUnitDat)
		{
			UnitBuildQueue.Push(BuildableUnit);
		}
	}
}

void EUnitFactoryBase::RemoveUnitFromQueue(const FVisualUnitData& InVisualUnitData)
{
	for (ContainerInt i = UnitBuildQueue.Size() - 1; i >= 0; i--)
	{
		const FConstructionUnitData& UnitInQueue = UnitBuildQueue[i];

		if (UnitInQueue.VisualUnitData == InVisualUnitData)
		{
			// Remove first found occurence
			UnitBuildQueue.RemoveAt(i);

			break;
		}
	}
}

void EUnitFactoryBase::CreateUnitList()
{
	BuildableUnitsArray.Clear();
	BuildableUnitsForWidgetArray.Clear();

	FVisualUnitData MeleeVisualUnitData("Melee unit", RTSAssetCollection::UnitBase);
	FVisualUnitData RangedVisualUnitData("Ranged unit", RTSAssetCollection::UnitBase);

	AddBuildableUnit(MeleeVisualUnitData);
	AddBuildableUnit(RangedVisualUnitData);
}

void EUnitFactoryBase::AddBuildableUnit(const FConstructionUnitData& InConstructionUnitData)
{
	// Create buildable unit
	BuildableUnitsArray.Push(InConstructionUnitData);

	// Create element in array for widget display
	BuildableUnitsForWidgetArray.Push(InConstructionUnitData.VisualUnitData);
}

void EUnitFactoryBase::OnUnitBuildFinish(FOptionalTimerParams* OptionalTimerParams)
{
	FactoryState = EFactoryState::BuildingUnitFinished;

	/** Current unit being built */
	FConstructionUnitData CurrentConstructionUnitData = UnitBuildQueue[0];

	// Remove from queue
	UnitBuildQueue.RemoveAt(0);

	// Create new unit entity
	CreateUnit();
}

void EUnitFactoryBase::CreateUnit()
{
	LOG_INFO("Create unit");
}
