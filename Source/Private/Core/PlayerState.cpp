// Created by Przemys³aw Wiewióra 2024

#include "GamePCH.h"
#include "Core/PlayerState.h"

FRTSPlayerState::FRTSPlayerState(const FUserId& InUserId)
	: FPlayerState(InUserId)
{
}

FPlayerResources& FRTSPlayerState::GetPlayerResources()
{
	return PlayerResources;
}
