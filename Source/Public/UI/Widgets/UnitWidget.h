#pragma once

#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

class FImageWidget;

class FUnitWidget : public FVerticalBoxWidget
{
public:
	FUnitWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Begin FWidget */
	void Init() override;
	/** End FWidget */

	void SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const;

protected:
	FImageWidget* ChildImageWidget;

};
