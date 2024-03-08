#include "GamePCH.h"
#include "UI/GamePauseMenu.h"

#include "Core/CustomGameEngine.h"
#include "Core/GameModes/RTSMainMenuGameMode.h"
#include "Engine/Logic/GameModeBase.h"
#include "Engine/Logic/GameModeManager.h"
#include "Input/EventHandler.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"
#include "UI/MainMenu.h"

FGamePauseMenu::FGamePauseMenu(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, VerticalBoxWidget(nullptr)
	, bIsVisible(false)
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.EscapeDelegate.Get();

	EscapeDelegate->Delegate.BindObject(this, &FGamePauseMenu::OnEscapePressed);
}

FGamePauseMenu::~FGamePauseMenu()
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.EscapeDelegate.Get();

	EscapeDelegate->Delegate.UnBindObject(this, &FGamePauseMenu::OnEscapePressed);
}

void FGamePauseMenu::Initialize()
{
	// Create VerticalBoxWidget
	VerticalBoxWidget = GetOwnerWindow()->CreateWidget<FVerticalBoxWidget>();
	VerticalBoxWidget->SetAnchor(EAnchor::Center);

	FButtonWidget* BackButton = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* TextWidget = BackButton->CreateWidget<FTextWidget>();
	TextWidget->SetText("Back to menu");
	BackButton->OnClickRelease.BindObject(this, &FGamePauseMenu::OnExitToMenuRequested);
}

void FGamePauseMenu::DeInitialize()
{
	VerticalBoxWidget->DestroyWidget();
}

void FGamePauseMenu::OnEscapePressed(EInputState InputState)
{
	if (InputState == EInputState::RELEASE)
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

void FGamePauseMenu::OnExitToMenuRequested()
{
	const FWindowAdvanced* WindowAdvanced = GetOwnerWindow<FWindowAdvanced>();
	if (WindowAdvanced != nullptr)
	{
		LOG_DEBUG("Exit to menu requested");

		FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
		MapManager->DeactivateCurrentGameMap();
		MapManager->UnloadAllMaps();

		DisablePauseMenu();

		WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSMainMenuGameMode>(true);
	}
	else
	{
		LOG_ERROR("WindowAdvanced is nullptr!");
	}
}

void FGamePauseMenu::DisablePauseMenu()
{
	bIsVisible = false;

	Hide();
}

void FGamePauseMenu::EnablePauseMenu()
{
	bIsVisible = true;

	Show();
}

void FGamePauseMenu::Show()
{
	if (IsInitialized())
	{
		VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Visible);
	}
	else
	{
		InitializePublic();
	}
}

void FGamePauseMenu::Hide()
{
	VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Collapsed);
}
