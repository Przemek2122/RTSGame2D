#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"
#include "ECS/UnitFactoryBase.h"

class EUnitFactoryBase;
class FFactoryUnitWidget;

enum class EFactoryDisplayMode
{
	DisplayAsImage,
	DisplayToCreateUnits,
};

/**
 * Widget for factory on UserUI
 */
class FFactoryWidget : public FVerticalBoxWidget
{
public:
	FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Set factory entity. Will also generate UI for factory. */
	void SetFactoryEntity(EUnitFactoryBase* InFactoryEntity);

protected:
	/** Open a menu of Units this factory can create */
	void CreateUnitsArray();

	/** Constructs array with unit list available in factory */
	virtual void CreateConstructUnitList();

private:
	/** Image for each unit displayed in factory */
	CArray<FFactoryUnitWidget*> UnitsAvailable;

	/** Array of available units */
	CArray<FConstructionUnitData> ConstructionUnitDataArray;

	/** Owning factory entity */
	EUnitFactoryBase* FactoryEntity;

};
