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

	/** Set images. Also sets display to image instead of unit production */
	void SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const;

	/** Open menu with units to construct selection */
	void OpenUnitsConstructionMenu();

protected:
	/** Open a menu of Units this factory can create */
	void CreateUnitsArray();

	/** Instead of menu - create an image of factory selected */
	void CreateImageOfFactory();

	/** Constructs array with unit list available in factory */
	virtual void ConstructUnitList(CArray<FConstructionUnitData>& ConstructionUnitDataArray);

	/** Returns display name of factory which is shown to user on UI */
	virtual std::string GetFactoryDisplayName() const;

private:
	/** Image used in case when EFactoryDisplayMode::DisplayAsImage */
	FImageWidget* ChildImageWidget;

	/** Image for each unit displayed in factory */
	CArray<FFactoryUnitWidget*> UnitsAvailable;

	FHorizontalBoxWidget* ContentHorizontalBoxWidget;

};
