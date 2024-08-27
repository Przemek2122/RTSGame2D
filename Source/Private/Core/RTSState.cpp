#include "GamePCH.h"
#include "Core/RTSState.h"

ERTSState::ERTSState(FEntityManager* InEntityManager)
	: EState(InEntityManager)
{
}

FUserResources& ERTSState::GetUserResources()
{
	return UserResources;
}
