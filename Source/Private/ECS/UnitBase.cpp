#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UTransformComponent>("TransformComponent");
	TransformComponent->SetLocationFinal({ 140, 151 });

	RenderComponent = CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImage("Unit1", R"(Assets\Textures\Units\UnitBase.png)");
	RenderComponent->SetImageSize({ 32, 32 });

}
