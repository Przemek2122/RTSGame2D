#include "GamePCH.h"
#include "UI/PersistentMenu.h"

#include "Renderer/Widgets/Samples/MouseSparkWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FPersistentMenu::FPersistentMenu(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, TextFPSWidget(nullptr)
{
}

void FPersistentMenu::Initialize()
{
	FWidgetManager* WidgetManager = GetOwnerWindow()->GetWidgetManager();

	WidgetManager->CreateWidget<FMouseSparkWidget>("MouseSparkWidget", 100);

	TextFPSWidget = WidgetManager->CreateWidget<FTextWidget>("TextFPS");
	TextFPSWidget->SetText("FPS");
	TextFPSWidget->SetAnchor(EAnchor::RightTop);
}

void FPersistentMenu::DeInitialize()
{
	TextFPSWidget->DestroyWidget();
}

FTextWidget* FPersistentMenu::GetFPSTextWidget() const
{
	return TextFPSWidget;
}
