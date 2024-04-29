#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

class FImageWidget;

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

	void SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const;

protected:
	FImageWidget* ChildImageWidget;

};