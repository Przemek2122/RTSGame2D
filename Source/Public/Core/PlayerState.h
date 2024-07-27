// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "PlayerResources.h"
#include "Engine/Logic/UserState.h"

/**
 * State of the Player
 */
class FRTSPlayerState : public FPlayerState
{
public:
	FRTSPlayerState(const FUserId& InUserId);

	FPlayerResources& GetPlayerResources();

protected:
	FPlayerResources PlayerResources;

};
