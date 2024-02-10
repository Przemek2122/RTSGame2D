#pragma once

#include "CoreMinimal.h"

class FVerticalBoxWidget;
class FGameMode;

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
class FMainMenu
{
public:
	FMainMenu(FWindow* InGameWindow, FGameMode* InGameMode);
	~FMainMenu();

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
	FWindow* GameWindow;
	FGameMode* GameMode;
	FVerticalBoxWidget* VerticalBoxWidget;

	EMainMenuState MainMenuState;

};
