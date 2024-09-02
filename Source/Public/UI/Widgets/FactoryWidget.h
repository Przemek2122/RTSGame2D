#pragma once

#include "CoreMinimal.h"
#include "Assets/Collection/AssetCollectionItem.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

class FFactoryUnitWidget;

enum class EFactoryDisplayMode
{
	DisplayAsImage,
	DisplayToCreateUnits,
};

struct FConstructionUnitData
{
	FConstructionUnitData() = default;

	FConstructionUnitData(const std::string& InName, FAssetCollectionItem InAssetCollectionItem);

	/** Name of the unit */
	std::string Name;

	/** Image to display */
	FAssetCollectionItem AssetCollectionItem;

};

/**
 * Widget for factory on UserUI
 */
class FFactoryWidget : public FVerticalBoxWidget
{
public:
	FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Begin FWidget */
	void Init() override;
	/** End FWidget */

	/** Open menu with units to construct selection */
	void OpenUnitsConstructionMenu();

protected:
	/** Open a menu of Units this factory can create */
	void CreateUnitsArray();

	/** Constructs array with unit list available in factory */
	virtual void ConstructUnitList(CArray<FConstructionUnitData>& ConstructionUnitDataArray);

	/** Returns display name of factory which is shown to user on UI */
	virtual std::string GetFactoryDisplayName() const;

private:
	/** Image for each unit displayed in factory */
	CArray<FFactoryUnitWidget*> UnitsAvailable;

};
