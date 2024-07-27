// Created by Przemys�aw Wiewi�ra 2024

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
