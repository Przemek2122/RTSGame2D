#pragma once

#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

class FTextWidget;

class FFactoryUnitWidget : public FVerticalBoxWidget
{
public:
	FFactoryUnitWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Begin FWidget */
	void Init() override;
	/** End FWidget */

	void SetUnitImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath);
	void SetUnitName(const std::string& UnitName);

protected:
	/** Name of the unit */
	std::string UnitName;

	/** Widget for unit image */
	FImageWidget* UnitImageWidget;

	/** Widget for unit name */
	FTextWidget* UnitTextWidget;

};
