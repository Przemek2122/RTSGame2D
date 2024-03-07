#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

class FVerticalBoxWidget;
class FRTSGameMode;

enum class EMainMenuState
{
	None = 0,
	MainMenu,
	GameMenu,
	EditorMenu
};

/**
 * Class for game MainMenu
 */
class FMainMenu : public FUIMenu
{
public:
	FMainMenu(FWindow* InGameWindow, FRTSGameMode* InGameMode);

	/** Generates default menu layout */
	void Initialize();

	/** Clears widgets and calls delegate */
	void DeInitialize();

	void OpenMainMenu();

	bool IsMenuNone() const { return (MainMenuState == EMainMenuState::None); }

protected:
	void InitializeMainMenuWidgets();
	void GameSelected();
	void EditorSelected();

	void InitializeGameWidgets();

	void InitializeEditorWidgets();

protected:
	FRTSGameMode* GameMode;
	FVerticalBoxWidget* VerticalBoxWidget;

	EMainMenuState MainMenuState;

};
