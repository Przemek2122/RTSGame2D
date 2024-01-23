#pragma once

#include "CoreMinimal.h"

class FVerticalBoxWidget;
class FGameMode;

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

};
