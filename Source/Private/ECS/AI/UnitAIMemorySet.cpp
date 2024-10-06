#include "GamePCH.h"
#include "ECS/AI/UnitAIMemorySet.h"

FUnitAIMemorySet::FUnitAIMemorySet()
	: ThisUnit(nullptr)
	, CurrentTarget(nullptr)
	, EnemyDetectionDistance(0)
	, EnemyTargetMemoryDistance(120)
{
}
