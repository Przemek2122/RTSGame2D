// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "ECS/AI/AIMemorySet.h"

/**
 * AI Memory set for units
 */
class FUnitAIMemorySet : public FAIMemorySet
{
public:
	FUnitAIMemorySet();

	/** Pointer to owning unit */
	EUnitBase* ThisUnit;

	/** Current enemy target for unit */
	EEntity* CurrentTarget;

	/** @TODO Unused (Implement in FAIActionFindTarget) - How far should this unit detect other units */
	int32 EnemyDetectionDistance;

	/** How far should unit remember hostile @CurrentTarget */
	int32 EnemyTargetMemoryDistance;

	/** Array with found hostiles */
	CArray<EEntity*> HostileEntitiesFound;

	/** Array with available hostiles */
	FDelegate<void, const CArray<EEntity*>> OnHostileEntitiesFound;

	/** Called when hostile is found */
	FDelegate<void, EEntity*> OnRandomHostileFound;

};
