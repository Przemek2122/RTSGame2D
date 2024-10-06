#include "GamePCH.h"
#include "UI/MainMenu.h"

#include "Core/GameModes/RTSGameMode.h"
#include "Core/GameModes/RTSGameModeEditor.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Mapmanager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"
#include "Timer/TimerManager.h"

FMainMenu::FMainMenu(FWindowAdvanced* InGameWindowAdvanced)
	: FUIMenu(InGameWindowAdvanced)
	, VerticalBoxWidget(nullptr)
	, MainMenuState(EMainMenuState::None)
{
}

void FMainMenu::Initialize()
{
	if (VerticalBoxWidget == nullptr)
	{
		const size_t Nanosecond_Start = FUtil::GetNanoSeconds();

		VerticalBoxWidget = GetOwnerWindow()->GetWidgetManager()->CreateWidget<FVerticalBoxWidget>("VerticalBox_MainMenu");

		InitializeMainMenuWidgets();

		const size_t Nanosecond_End = FUtil::GetNanoSeconds();
		const size_t Nanosecond_TestDuration = Nanosecond_End - Nanosecond_Start;
		const std::string ActualTimeString = std::to_string(FUtil::NanoSecondToSecond(Nanosecond_TestDuration));
		LOG_INFO("MainMenu init duration: " + ActualTimeString + "s.");
	}
	else
	{
		LOG_WARN("VerticalBoxWidget is already initialized!");
	}
}

void FMainMenu::DeInitialize()
{
	if (VerticalBoxWidget != nullptr)
	{
		// Clear current widgets
		VerticalBoxWidget->DestroyWidget();
	}
}

void FMainMenu::OpenMainMenu()
{
	if (VerticalBoxWidget != nullptr)
	{
		InitializeMainMenuWidgets();
	}
	else
	{
		LOG_ERROR("VerticalBoxWidget is null!");
	}
}

void FMainMenu::InitializeMainMenuWidgets()
{
	VerticalBoxWidget->SetAnchor(EAnchor::Center);

	FButtonWidget* StartGameButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* StartGameTextWidget = StartGameButtonWidget->CreateWidget<FTextWidget>();
	StartGameTextWidget->SetText("Open Game");
	StartGameButtonWidget->OnLeftClickPress.BindObject(this, &FMainMenu::GameSelected);
	StartGameButtonWidget->UseDefaultSize();

	FButtonWidget* StartEditorButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* StartEditorTextWidget = StartEditorButtonWidget->CreateWidget<FTextWidget>();
	StartEditorTextWidget->SetText("Open Editor");
	StartEditorButtonWidget->OnLeftClickPress.BindObject(this, &FMainMenu::EditorSelected);
	StartEditorButtonWidget->UseDefaultSize();

	FButtonWidget* ExitButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* ExitTextWidget = ExitButtonWidget->CreateWidget<FTextWidget>();
	ExitTextWidget->SetText("Exit");
	ExitButtonWidget->OnLeftClickPress.BindObject(this, &FMainMenu::Exit);
	ExitButtonWidget->UseDefaultSize();

	MainMenuState = EMainMenuState::MainMenu;
}

void FMainMenu::GameSelected()
{
	VerticalBoxWidget->ClearChildren();

	InitializeGameWidgets();

	MainMenuState = EMainMenuState::GameMenu;
}

void FMainMenu::EditorSelected()
{
	VerticalBoxWidget->ClearChildren();

	InitializeEditorWidgets();

	MainMenuState = EMainMenuState::EditorMenu;
}

void FMainMenu::Exit()
{
	VerticalBoxWidget->ClearChildren();

	GEngine->RequestExit();
}

void FMainMenu::InitializeGameWidgets()
{
	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	if (MapManager != nullptr)
	{
		MapManager->CacheAvailableMaps();

		VerticalBoxWidget->SetAnchor(EAnchor::Center);

		FTextWidget* GameInfoTextWidget = VerticalBoxWidget->CreateWidget<FTextWidget>("GameInfoTextWidget");
		GameInfoTextWidget->SetText("Game maps:");

		CArray<std::string> AvailableMaps = MapManager->GetAvailableMaps();
		for (std::string& AvailableMap : AvailableMaps)
		{
			FButtonWidget* AvailableMapButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>("Button_" + AvailableMap);
			AvailableMapButtonWidget->UseDefaultSize();

			AvailableMapButtonWidget->OnLeftClickRelease.BindLambda([&, AvailableMap]
			{
				LOG_DEBUG("Selected: " << AvailableMap);

				FMapAsset* LoadedMap = GetOwnerWindow()->GetMapManager()->LoadMap(AvailableMap);
				GetOwnerWindow()->GetMapManager()->SetActiveGameMap(LoadedMap);

				const FWindowAdvanced* WindowAdvanced = GetOwnerWindow<FWindowAdvanced>();
				if (WindowAdvanced != nullptr)
				{
					MainMenuState = EMainMenuState::None;

					WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSGameMode>(true);
				}
			});

			FTextWidget* AvailableMapTextWidget = AvailableMapButtonWidget->CreateWidget<FTextWidget>("Text_" + AvailableMap);
			AvailableMapTextWidget->SetText(AvailableMap);
		}

		FButtonWidget* BackButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		BackButtonWidget->CreateWidget<FTextWidget>()->SetText("Back");
		BackButtonWidget->UseDefaultSize();
		BackButtonWidget->OnLeftClickRelease.BindLambda([&]()
		{
			LOG_DEBUG("Back requested!");

			VerticalBoxWidget->ClearChildren();

			InitializeMainMenuWidgets();
		});
	}
	else
	{
		LOG_ERROR("MapManager is null!");
	}
}

void FMainMenu::InitializeEditorWidgets()
{
	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	if (MapManager != nullptr)
	{
		MapManager->CacheAvailableMaps();

		VerticalBoxWidget->SetAnchor(EAnchor::Center);

		FTextWidget* EditorInfoTextWidget = VerticalBoxWidget->CreateWidget<FTextWidget>("EditorInfoTextWidget");
		EditorInfoTextWidget->SetText("Editor maps:");

		CArray<std::string> AvailableMaps = MapManager->GetAvailableMaps();
		for (std::string& AvailableMap : AvailableMaps)
		{
			FButtonWidget* AvailableMapButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
			AvailableMapButtonWidget->UseDefaultSize();
			AvailableMapButtonWidget->OnLeftClickRelease.BindLambda([&, AvailableMap]()
			{
				LOG_DEBUG("Selected editor map: " << AvailableMap);

				FMapAsset* LoadedMap = GetOwnerWindow()->GetMapManager()->LoadMap(AvailableMap);
				GetOwnerWindow()->GetMapManager()->SetActiveEditorMap(LoadedMap);

				const FWindowAdvanced* WindowAdvanced = GetOwnerWindow<FWindowAdvanced>();
				if (WindowAdvanced != nullptr)
				{
					WindowAdvanced->GetGameModeManager()->CreateGameMode<FRTSGameModeEditor>(true);

					MainMenuState = EMainMenuState::None;
				}
			});

			FTextWidget* AvailableMapTextWidget = AvailableMapButtonWidget->CreateWidget<FTextWidget>();
			AvailableMapTextWidget->SetText(AvailableMap);
		}

		FButtonWidget* BackButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		BackButtonWidget->UseDefaultSize();
		BackButtonWidget->CreateWidget<FTextWidget>()->SetText("Back");
		BackButtonWidget->OnLeftClickRelease.BindLambda([&]()
		{
			LOG_DEBUG("Back requested!");

			VerticalBoxWidget->ClearChildren();

			InitializeMainMenuWidgets();
		});
	}
	else
	{
		LOG_ERROR("MapManager is null!");
	}
}
