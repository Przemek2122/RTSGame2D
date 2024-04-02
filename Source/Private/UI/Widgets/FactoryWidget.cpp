#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"

#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ChildImageWidget(nullptr)
	, ChildTextWidget(nullptr)
{
}

void FFactoryWidget::Init()
{
	Super::Init();

	SetScaleToContent(true);

	ChildImageWidget = CreateWidget<FImageWidget>();

	ChildTextWidget = CreateWidget<FTextWidget>();
	ChildTextWidget->SetText("Unnamed factory");
}

void FFactoryWidget::SetFactoryDisplayName(const std::string& InFactoryDisplayName) const
{
	ChildTextWidget->SetText(InFactoryDisplayName);
}

void FFactoryWidget::SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const
{
	ChildImageWidget->SetImage(InFactoryImageName, InFactoryImagePath);
}
