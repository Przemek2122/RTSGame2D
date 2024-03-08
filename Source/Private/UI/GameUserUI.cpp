#include "GamePCH.h"
#include "UI/GameUserUI.h"

#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FGameUserUI::FGameUserUI(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, MainHorizontalBox(nullptr)
{
}

void FGameUserUI::Initialize()
{
	MainHorizontalBox = GetOwnerWindow()->CreateWidget<FHorizontalBoxWidget>();
	MainHorizontalBox->SetAnchor(EAnchor::BottomCenter);
	MainHorizontalBox->SetWidgetSizePercent({ 1.f, 0.25f });

	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt 23");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample txt 123 12 4124 ");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample 23");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("Sample  12341 124");
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("F 124  12341 124");

}

void FGameUserUI::DeInitialize()
{
	MainHorizontalBox->DestroyWidget();
}
