#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	CreateComponent<UTransformComponent>("TransformComponent");
	CreateComponent<URenderComponent>("RenderComponent");



}
