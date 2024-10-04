#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"
#include "ECS/UnitBase.h"
#include "Timer/Timer.h"

class FProgressBarWidget;
class UWidgetAttachmentComponent;
class USquareCollisionComponent;
class URenderComponent;

enum class EFactoryState : uint8
{
	Idle,
	BuildingUnit,
	BuildingUnitFinished
};

/** Unit data for widget */
struct FVisualUnitData
{
	FVisualUnitData() = default;
	FVisualUnitData(const std::string& InName, FAssetCollectionItem InAssetCollectionItem);

	/** Name of the unit */
	std::string Name;

	/** Image to display */
	FAssetCollectionItem AssetCollectionItem;

	bool operator==(const FVisualUnitData& Other) const
	{
		return (Name == Other.Name);
	}
};

/** Unit data for building and queue */
struct FConstructionUnitData
{
	FConstructionUnitData();
	FConstructionUnitData(FVisualUnitData InVisualUnitData);

	/** Visual representation of the widget (for factory widget) */
	FVisualUnitData VisualUnitData;

	/** What is the time required to create an unit in factory? */
	float TimeToBuildUnit;

	/** Class to create */
	FEntityClassStorage<EUnitBase> StoredClass;
	
};

class EUnitFactoryBase : public EInteractableEntityBase
{
public:
	EUnitFactoryBase(FEntityManager* InEntityManager);
	~EUnitFactoryBase() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	/** End EEntity */

	/** Begin IScreenSelectionInterface */
	FVector2D<int> GetLocation() override;
	FVector2D<int> GetSize() override;
	void OnSelect() override;
	void OnDeSelect() override;
	/** End IScreenSelectionInterface */

	/** Override to choose factory asset */
	virtual const FAssetCollectionItem& GetFactoryAsset() const;

	/** Override to choose factory name */
	virtual std::string GetFactoryName() const;

	const CArray<FVisualUnitData>& GetUnits() const;

	/** Adds one unit to build queue */
	void AddUnitToQueue(const FVisualUnitData& InVisualUnitDat);

	/** Removes unit from build queue (if present) */
	void RemoveUnitFromQueue(const FVisualUnitData& InVisualUnitDat);

	UParentComponent* GetTransformComponent() const { return TransformComponent; }
	URenderComponent* GetRenderComponent() const { return RenderComponent; }
	USquareCollisionComponent* GetSquareCollisionComponent() const { return SquareCollisionComponent; }
	UWidgetAttachmentComponent* GetBuildProgressBarAttachmentComponent() const { return BuildProgressBarAttachmentComponent; }

protected:
	/** Create list of buildable units */
	virtual void CreateUnitList();

	/** Add buildable unit to arrays */
	void AddBuildableUnit(const FConstructionUnitData& InConstructionUnitData);

	/** Called by timer when unit building finished and unit should be created */
	void OnUnitBuildFinish(FOptionalTimerParams* OptionalTimerParams);

	/** Called by OnUnitBuildFinish when unit should be created */
	void CreateUnit();

private:
	/** Root transform component */
	UParentComponent* TransformComponent;

	/** Component for spawn location of new unit */
	UComponent* NewUnitSpawnLocationComponent;

	/** Render component for factory */
	URenderComponent* RenderComponent;

	/** Square collision for Factory */
	USquareCollisionComponent* SquareCollisionComponent;

	/** Progress bar for widget attachment for building progress display */
	UWidgetAttachmentComponent* BuildProgressBarAttachmentComponent;

	/** Progress bar widget for build progress */
	FProgressBarWidget* BuildProgressBarWidget;

	/** All factory units which can be built */
	CArray<FConstructionUnitData> BuildableUnitsArray;

	/** Part of BuildableUnitsArray for widgets */
	CArray<FVisualUnitData> BuildableUnitsForWidgetArray;

	/** Build queue for units in this factory */
	CArray<FConstructionUnitData> UnitBuildQueue;

	/** Timer used for building unit */
	std::shared_ptr<FTimer> UnitBuildTimer;

	/** What is factory currently doing */
	EFactoryState FactoryState;

	/** What is the offset for new unit location spawn? */
	FVector2D<float> NewUnitSpawnLocationOffset;

	/** What is the offset for new unit rotation spawn? */
	float NewUnitSpawnRotationOffset;

};
