#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ChildImageWidget(nullptr)
{
}

void FFactoryWidget::Init()
{
	Super::Init();

	SetScaleToContent(true);

	ChildImageWidget = CreateWidget<FImageWidget>();
}

void FFactoryWidget::SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const
{
	ChildImageWidget->SetImage(InFactoryImageName, InFactoryImagePath);
}