// Created by Przemys³aw Wiewióra 2024

#include "GamePCH.h"
#include "Core/RTSPlayerController.h"

#include "Core/RTSHUD.h"
#include "Core/RTSState.h"

FRTSPlayerController::FRTSPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId)
	: FPlayerController(InEntityManager, InUserId)
{
}

EState* FRTSPlayerController::CreateState(FEntityManager* EntityManager)
{
	return EntityManager->CreateEntity<ERTSState>();
}

EHUDBase* FRTSPlayerController::CreateHUD(FEntityManager* EntityManager)
{
	return EntityManager->CreateEntity<ERTSHUD>();
}
