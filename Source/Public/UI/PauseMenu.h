#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

enum class EInputState;
class FRTSGameEngine;
class FVerticalBoxWidget;

class FPauseMenu : public FUIMenu
{
public:
	FPauseMenu(FWindow* InGameWindow, FRTSGameEngine* InRTSGameEngine);
	~FPauseMenu() override;

	/** Generates default menu layout */
	void Initialize();

	bool CanBeOpened() const;

	void OnEscapePressed(EInputState InputState);

	void OnExitToMenuRequested();

protected:
	void DisablePauseMenu();
	void EnablePauseMenu();

	void Show();
	void Hide();

protected:
	FRTSGameEngine* RTSGameEngine;

	FVerticalBoxWidget* VerticalBoxWidget;

	bool bIsVisible;
	bool bIsInitialised;

};
