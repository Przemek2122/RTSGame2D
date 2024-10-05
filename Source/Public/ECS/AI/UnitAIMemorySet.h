// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "ECS/AI/AIMemorySet.h"

/**
 * AI Memory set for units
 */
class FUnitAIMemorySet : public FAIMemorySet
{
public:
	/** Array with found hostiles */
	CArray<EEntity*> HostileEntitiesFound;

	/** Current enemy target for unit */
	EUnitBase* CurrentTarget;

};
