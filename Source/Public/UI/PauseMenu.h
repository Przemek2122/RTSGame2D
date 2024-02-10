#pragma once

#include "CoreMinimal.h"

class FRTSGameEngine;
class FVerticalBoxWidget;

class FPauseMenu
{
public:
	FPauseMenu(FWindow* InGameWindow, FRTSGameEngine* InRTSGameEngine);
	virtual ~FPauseMenu();

	/** Generates default menu layout */
	void Initialize();

	bool CanBeOpened();

	void OnEscapePressed(EInputState InputState);

	void OnExitToMenuRequested();

protected:
	void DisablePauseMenu();
	void EnablePauseMenu();

	void Show();
	void Hide();

protected:
	FWindow* GameWindow;
	FRTSGameEngine* RTSGameEngine;

	FVerticalBoxWidget* VerticalBoxWidget;

	bool bIsVisible;
	bool bIsInitialised;

};
