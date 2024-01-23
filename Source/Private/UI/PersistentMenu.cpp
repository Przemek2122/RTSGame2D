#include "GamePCH.h"
#include "UI/PersistentMenu.h"

#include "Renderer/Widgets/Samples/MouseSparkWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FPersistentMenu::FPersistentMenu(FWindow* InGameWindow)
	: GameWindow(InGameWindow)
	, TextFPSWidget(nullptr)
{
}

void FPersistentMenu::Initialize()
{
	GameWindow->GetWidgetManager()->CreateWidget<FMouseSparkWidget>("MouseSparkWidget", 100);
	TextFPSWidget = GameWindow->GetWidgetManager()->CreateWidget<FTextWidget>("TextFPS");
	TextFPSWidget->SetText("FPS");
	TextFPSWidget->SetAnchor(EAnchor::RightTop);
}

FTextWidget* FPersistentMenu::GetFPSTextWidget() const
{
	return TextFPSWidget;
}
