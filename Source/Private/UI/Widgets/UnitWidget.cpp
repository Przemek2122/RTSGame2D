#include "GamePCH.h"
#include "UI/Widgets/UnitWidget.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"

FUnitWidget::FUnitWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ChildImageWidget(nullptr)
{
}

void FUnitWidget::Init()
{
	Super::Init();

	SetScaleToContent(true);

	ChildImageWidget = CreateWidget<FImageWidget>();
}

void FUnitWidget::SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const
{
	ChildImageWidget->SetImage(InFactoryImageName, InFactoryImagePath);
}
