#include "GamePCH.h"
#include "UI/UserUI.h"

#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FUserUI::FUserUI(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, MainHorizontalBox(nullptr)
{
}

ETickPhase FUserUI::GetTickPhase() const
{
	return ETickPhase::Default;
}

void FUserUI::Tick(float DeltaTime)
{
	LOG_INFO("TICK");
}

void FUserUI::InitializeUI()
{
	MainHorizontalBox = GetOwnerWindow()->CreateWidget<FHorizontalBoxWidget>();
	MainHorizontalBox->SetAnchor(EAnchor::BottomCenter);
	MainHorizontalBox->SetWidgetSizePercent({ 1.f, 0.3f });

	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt 23");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt 123 12 4124 ");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample 23");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample  12341 124");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("F 124  12341 124");

}

void FUserUI::DeInitializeUI()
{
}
