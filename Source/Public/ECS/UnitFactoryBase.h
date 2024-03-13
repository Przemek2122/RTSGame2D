#pragma once

#include "Core/ECS/Entity.h"

class EUnitFactoryBase : public EEntity
{
public:
	EUnitFactoryBase(FEntityManager* InEntityManager);
	virtual ~EUnitFactoryBase();



};
