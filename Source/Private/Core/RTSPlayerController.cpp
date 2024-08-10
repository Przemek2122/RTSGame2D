// Created by Przemys�aw Wiewi�ra 2024

#include "GamePCH.h"
#include "Core/RTSPlayerController.h"

FRTSPlayerController::FRTSPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId)
	: FPlayerController(InEntityManager, InUserId)
{
}

void FRTSPlayerController::BeginPlay()
{
	FPlayerController::BeginPlay();
}

FPlayerResources& FRTSPlayerController::GetPlayerResources()
{
	return PlayerResources;
}
