#pragma once

#include "Core\ECS\Entity.h"

class UTransformComponent;
class URenderComponent;

class EUnitBase : public EEntity
{
public:
	EUnitBase(FEntityManager* InEntityManager);
	~EUnitBase() override = default;

protected:
	UTransformComponent* TransformComponent;
	URenderComponent* RenderComponent;
};
