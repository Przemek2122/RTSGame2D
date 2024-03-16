#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UTransformComponent>("TransformComponent");
	RenderComponent = CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImage("Factory5", R"(Assets\Textures\Factories\Factory5.png)");


}
