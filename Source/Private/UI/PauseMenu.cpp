#include "GamePCH.h"
#include "UI/PauseMenu.h"

#include "Core/CustomGameEngine.h"
#include "Input/EventHandler.h"
#include "Renderer/Map/Mapmanager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"
#include "UI/MainMenu.h"

FPauseMenu::FPauseMenu(FWindow* InGameWindow, FRTSGameEngine* InRTSGameEngine)
	: GameWindow(InGameWindow)
	, RTSGameEngine(InRTSGameEngine)
	, VerticalBoxWidget(nullptr)
	, bIsVisible(false)
	, bIsInitialised(false)
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.EscapeDelegate.Get();

	EscapeDelegate->Delegate.BindObject(this, &FPauseMenu::OnEscapePressed);
}

FPauseMenu::~FPauseMenu()
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.EscapeDelegate.Get();

	EscapeDelegate->Delegate.UnBindObject(this, &FPauseMenu::OnEscapePressed);
}

void FPauseMenu::Initialize()
{
	if (!bIsInitialised)
	{
		bIsInitialised = true;

		// Create VerticalBoxWidget
		VerticalBoxWidget = GameWindow->CreateWidget<FVerticalBoxWidget>();
		VerticalBoxWidget->SetAnchor(EAnchor::Center);

		FButtonWidget* BackButton = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		FTextWidget* TextWidget = BackButton->CreateWidget<FTextWidget>();
		TextWidget->SetText("Back to menu");
		BackButton->OnClickRelease.BindObject(this, &FPauseMenu::OnExitToMenuRequested);
	}
}

bool FPauseMenu::CanBeOpened()
{
	return RTSGameEngine->GetMainMenu()->IsMenuNone();
}

void FPauseMenu::OnEscapePressed(EInputState InputState)
{
	if (CanBeOpened() && InputState == EInputState::RELEASE)
	{
		if (bIsVisible)
		{
			DisablePauseMenu();
		}
		else
		{
			EnablePauseMenu();
		}
	}
}

void FPauseMenu::OnExitToMenuRequested()
{
	LOG_DEBUG("Exit to menu requested");

	GameWindow->GetMapManager()->UnLoadCurrentMap();

	RTSGameEngine->GetMainMenu()->OpenMainMenu();

	DisablePauseMenu();
}

void FPauseMenu::DisablePauseMenu()
{
	bIsVisible = false;

	Hide();
}

void FPauseMenu::EnablePauseMenu()
{
	bIsVisible = true;

	Show();
}

void FPauseMenu::Show()
{
	if (bIsInitialised)
	{
		VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Visible);
	}
	else
	{
		Initialize();
	}
}

void FPauseMenu::Hide()
{
	VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Collapsed);
}
