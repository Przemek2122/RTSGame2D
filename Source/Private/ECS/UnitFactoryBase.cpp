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

void EUnitFactoryBase::BeginPlay()
{
	EEntity::BeginPlay();

	RegisterToScreenSelection(GetEntityManagerOwner());
}

FVector2D<int> EUnitFactoryBase::GetLocation()
{
	if (TransformComponent != nullptr)
	{
		return TransformComponent->GetLocationFinal();
	}

	return { };
}

FVector2D<int> EUnitFactoryBase::GetSize()
{
	if (RenderComponent != nullptr)
	{
		return TransformComponent->GetSize();
	}

	return { };
}

void EUnitFactoryBase::OnSelection()
{
	LOG_DEBUG("FactoryBase selected");
}
