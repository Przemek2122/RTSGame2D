#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

class FWindowAdvanced;
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
 * Class for game MainMenu launched when game starts.
 */
class FMainMenu : public FUIMenu
{
public:
	FMainMenu(FWindowAdvanced* InGameWindowAdvanced);

	void OpenMainMenu();

	bool IsMenuNone() const { return (MainMenuState == EMainMenuState::None); }

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

	void InitializeMainMenuWidgets();

	void GameSelected();
	void EditorSelected();
	void Exit();

	void InitializeGameWidgets();
	void InitializeEditorWidgets();

protected:
	FVerticalBoxWidget* VerticalBoxWidget;

	EMainMenuState MainMenuState;

};
