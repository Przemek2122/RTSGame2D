#pragma once

#include "Core\Engine\Logic\BaseController.h"
#include "UI/GamePauseMenu.h"
#include "UI/GameUserUI.h"

class ERTSHUD : public EHUDBase
{
public:
	ERTSHUD(FEntityManager* InEntityManager);

	void BeginPlay() override;

	void OnGameStart();

	FGameUserUI* GetUserUI() const { return UserUIPtr.Get(); }

protected:
	/** User UI - There should be factory placing, units, and more */
	FAutoUIMenu<FGameUserUI> UserUIPtr;

	/** Pause menu - IN-GAME only */
	FAutoUIMenu<FGamePauseMenu> PauseMenuPtr;

};
