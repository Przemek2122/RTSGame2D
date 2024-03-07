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
	GetOwnerWindow()->GetWidgetManager()->CreateWidget<FMouseSparkWidget>("MouseSparkWidget", 100);

	TextFPSWidget = GetOwnerWindow()->GetWidgetManager()->CreateWidget<FTextWidget>("TextFPS");
	TextFPSWidget->SetText("FPS");
	TextFPSWidget->SetAnchor(EAnchor::RightTop);
}

FTextWidget* FPersistentMenu::GetFPSTextWidget() const
{
	return TextFPSWidget;
}
