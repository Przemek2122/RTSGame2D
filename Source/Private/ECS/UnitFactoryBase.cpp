#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "ECS/Components/TransformComponent.h"

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	CreateComponent<UTransformComponent>("TransformComponent");



}

EUnitFactoryBase::~EUnitFactoryBase()
{
}
