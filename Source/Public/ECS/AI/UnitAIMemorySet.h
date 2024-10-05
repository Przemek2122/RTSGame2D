// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "ECS/AI/AIMemorySet.h"

/**
 * AI Memory set for units
 */
class FUnitAIMemorySet : public FAIMemorySet
{
public:
	/** Current enemy target for unit */
	EEntity* CurrentTarget;

	/** Array with found hostiles */
	CArray<EEntity*> HostileEntitiesFound;

	/** Array with available hostiles */
	FDelegate<void, const CArray<EEntity*>> OnHostileEntitiesFound;

	/** Called when hostile is found */
	FDelegate<void, EEntity*> OnRandomHostileFound;

};
