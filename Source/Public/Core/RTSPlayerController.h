// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "PlayerResources.h"
#include "Engine/Logic/BaseController.h"

/**
 * Player controller
 */
class FRTSPlayerController : public FPlayerController
{
public:
	FRTSPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId);

	void BeginPlay() override;

	FPlayerResources& GetPlayerResources();

protected:
	FPlayerResources PlayerResources;

};
