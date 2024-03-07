#pragma once

#include "CoreMinimal.h"
#include "Interfaces/CoreLoop/ITickInterface.h"
#include "Renderer/Widgets/UIMenu.h"

class FHorizontalBoxWidget;

class FUserUI : public FUIMenu, public ITickInterface
{
public:
	FUserUI(FWindow* InGameWindow);

	ETickPhase GetTickPhase() const override;
	void Tick(float DeltaTime) override;

	void InitializeUI();
	void DeInitializeUI();

protected:
	FHorizontalBoxWidget* MainHorizontalBox;

};
