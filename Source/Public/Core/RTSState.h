#pragma once

#include "UserResources.h"
#include "Core\Engine\Logic\BaseController.h"

/**
 * State of user
 */
class ERTSState : public EState
{
public:
	ERTSState(FEntityManager* InEntityManager);

	FUserResources& GetUserResources();

protected:
	FUserResources UserResources;

};
