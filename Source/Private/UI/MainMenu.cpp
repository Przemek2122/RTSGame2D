#include "GamePCH.h"
#include "UI/MainMenu.h"

#include "Renderer/Map/Mapmanager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FMainMenu::FMainMenu(FWindow* InGameWindow, FGameMode* InGameMode)
	: GameWindow(InGameWindow)
	, GameMode(InGameMode)
	, VerticalBoxWidget(nullptr)
	, MainMenuState(EMainMenuState::None)
{
}

FMainMenu::~FMainMenu()
{
}

void FMainMenu::Initialize()
{
	if (VerticalBoxWidget == nullptr)
	{
		LOG_DEBUG("Init() started: '" << "FMainMenu" << "' starting ...");
		const size_t Nanosecond_Start = FUtil::GetNanoSeconds();

		VerticalBoxWidget = GameWindow->GetWidgetManager()->CreateWidget<FVerticalBoxWidget>("TestVerticalBoxWidget");

		InitializeMainMenuWidgets();

		const size_t Nanosecond_End = FUtil::GetNanoSeconds();
		const size_t Nanosecond_TestDuration = Nanosecond_End - Nanosecond_Start;
		const std::string ActualTimeString = std::to_string(FUtil::NanoSecondToSecond<float>(Nanosecond_TestDuration));
		LOG_DEBUG("MainMenu init duration (nanoseconds): " + ActualTimeString + "s.");
	}
	else
	{
		LOG_WARN("VerticalBoxWidget is already initialized!");
	}
}

void FMainMenu::DeInitialize()
{
	if (VerticalBoxWidget != nullptr && GameWindow != nullptr)
	{
		// Clear current widgets
		GameWindow->DestroyWidget(VerticalBoxWidget);
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
	StartGameButtonWidget->OnClickPress.BindObject(this, &FMainMenu::GameSelected);

	FButtonWidget* StartEditorButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* StartEditorTextWidget = StartEditorButtonWidget->CreateWidget<FTextWidget>();
	StartEditorTextWidget->SetText("Open Editor");
	StartEditorButtonWidget->OnClickPress.BindObject(this, &FMainMenu::EditorSelected);

	FButtonWidget* ExitButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* ExitTextWidget = ExitButtonWidget->CreateWidget<FTextWidget>();
	ExitTextWidget->SetText("Exit");
	ExitButtonWidget->OnClickPress.BindLambda( [this]
	{
		LOG_DEBUG("Exit requested!");

		VerticalBoxWidget->ClearChildren();

		GEngine->RequestExit();
	});

	MainMenuState = EMainMenuState::MainMenu;
}

void FMainMenu::GameSelected()
{
	LOG_DEBUG("Open Game requested!");

	VerticalBoxWidget->ClearChildren();

	InitializeGameWidgets();

	MainMenuState = EMainMenuState::GameMenu;
}

void FMainMenu::EditorSelected()
{
	LOG_DEBUG("Open Editor requested!");

	VerticalBoxWidget->ClearChildren();

	InitializeEditorWidgets();

	MainMenuState = EMainMenuState::EditorMenu;
}

void FMainMenu::InitializeGameWidgets()
{
	FMapManager* MapManager = GameWindow->GetMapManager();
	if (MapManager != nullptr)
	{
		MapManager->CacheAvailableMaps();

		VerticalBoxWidget->SetAnchor(EAnchor::Center);

		FTextWidget* GameInfoTextWidget = VerticalBoxWidget->CreateWidget<FTextWidget>("GameInfoTextWidget");
		GameInfoTextWidget->SetText("Game maps:");

		CArray<std::string> AvailableMaps = MapManager->GetAvailableMaps();
		for (std::string& AvailableMap : AvailableMaps)
		{
			FButtonWidget* AvailableMapButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();

			AvailableMapButtonWidget->OnClickRelease.BindLambda([&, AvailableMap]
			{
				LOG_DEBUG("Selected: " << AvailableMap);

				FMapAsset* LoadedMap = GameWindow->GetMapManager()->LoadMap(AvailableMap);
				GameWindow->GetMapManager()->SetActiveMap(LoadedMap);

				MainMenuState = EMainMenuState::None;

				VerticalBoxWidget->ClearChildren();
			});

			FTextWidget* AvailableMapTextWidget = AvailableMapButtonWidget->CreateWidget<FTextWidget>();
			AvailableMapTextWidget->SetText(AvailableMap);
		}

		FButtonWidget* BackButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		BackButtonWidget->CreateWidget<FTextWidget>()->SetText("Back");
		BackButtonWidget->OnClickRelease.BindLambda([&]()
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
	FMapManager* MapManager = GameWindow->GetMapManager();
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
			AvailableMapButtonWidget->OnClickRelease.BindLambda([&, AvailableMap]()
			{
				LOG_DEBUG("Clicked: " << AvailableMap);

				//MainMenuState = EMainMenuState::None;
			});
			FTextWidget* AvailableMapTextWidget = AvailableMapButtonWidget->CreateWidget<FTextWidget>();
			AvailableMapTextWidget->SetText(AvailableMap);
		}

		FButtonWidget* BackButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		BackButtonWidget->CreateWidget<FTextWidget>()->SetText("Back");
		BackButtonWidget->OnClickRelease.BindLambda([&]()
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
