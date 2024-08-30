#include "GamePCH.h"
#include "UI/Widgets/FactoryUnitWidget.h"

#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FFactoryUnitWidget::FFactoryUnitWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, UnitImageWidget(nullptr)
	, UnitTextWidget(nullptr)
{
}

void FFactoryUnitWidget::Init()
{
	Super::Init();

	UnitImageWidget = CreateWidget<FImageWidget>("UnitImage");
	UnitTextWidget = CreateWidget<FTextWidget>("UnitName");
}

void FFactoryUnitWidget::SetUnitImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath)
{
	UnitImageWidget->SetImage(InFactoryImageName, InFactoryImagePath);
}

void FFactoryUnitWidget::SetUnitName(const std::string& UnitName)
{
	UnitTextWidget->SetText(UnitName);
}
