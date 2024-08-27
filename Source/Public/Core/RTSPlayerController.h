// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/Logic/BaseController.h"

/**
 * Player controller
 */
class FRTSPlayerController : public FPlayerController
{
public:
	FRTSPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId);

protected:
	EState* CreateState(FEntityManager* EntityManager) override;
	EHUDBase* CreateHUD(FEntityManager* EntityManager) override;

};
