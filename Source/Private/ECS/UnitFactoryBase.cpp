#include "GamePCH.h"
#include "ECS/UnitFactoryBase.h"

#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

EUnitFactoryBase::EUnitFactoryBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UTransformComponent>("TransformComponent");
	TransformComponent->SetLocationFinal({ 64, 64 });

	RenderComponent = CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImage("Factory5", R"(Assets\Textures\Factories\FactoryBase.png)");
	RenderComponent->SetImageSize({ 64, 64 });
	
}
