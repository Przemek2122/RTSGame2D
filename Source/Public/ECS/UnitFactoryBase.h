#pragma once

#include "Core/ECS/Entity.h"

class UTransformComponent;
class URenderComponent;

class EUnitFactoryBase : public EEntity
{
public:
	EUnitFactoryBase(FEntityManager* InEntityManager);
	~EUnitFactoryBase() override = default;

protected:
	UTransformComponent* TransformComponent;
	URenderComponent* RenderComponent;

};
