// Created by Przemys³aw Wiewióra 2024

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
