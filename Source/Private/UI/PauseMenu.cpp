#include "GamePCH.h"
#include "UI/PauseMenu.h"

#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FPauseMenu::FPauseMenu(FWindow* InGameWindow)
	: GameWindow(InGameWindow)
	, VerticalBoxWidget(nullptr)
{
}

void FPauseMenu::Initialize()
{
	// Create VerticalBoxWidget
	VerticalBoxWidget = GameWindow->CreateWidget<FVerticalBoxWidget>();
	VerticalBoxWidget->SetAnchor(EAnchor::Center);

	FButtonWidget* BackButton = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* TextWidget = BackButton->CreateWidget<FTextWidget>();
	TextWidget->SetText("Back to menu");


}

void FPauseMenu::Show()
{
}

void FPauseMenu::Hide()
{
}


