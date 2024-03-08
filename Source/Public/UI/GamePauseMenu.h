#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

enum class EInputState;
class FRTSGameEngine;
class FVerticalBoxWidget;

class FGamePauseMenu : public FUIMenu
{
public:
	FGamePauseMenu(FWindow* InGameWindow);
	~FGamePauseMenu() override;

	void OnEscapePressed(EInputState InputState);

	void OnExitToMenuRequested();

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

	void DisablePauseMenu();
	void EnablePauseMenu();

	void Show();
	void Hide();

protected:
	FVerticalBoxWidget* VerticalBoxWidget;

	bool bIsVisible;

};
