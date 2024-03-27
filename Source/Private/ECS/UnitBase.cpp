#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UTransformComponent>("TransformComponent");
	TransformComponent->SetLocationFinal({ 140, 151 });

	RenderComponent = CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImage("Unit", R"(Assets\Textures\Units\UnitBase.png)");
	RenderComponent->SetImageSize({ 32, 32 });

	HealthComponent = CreateComponent<UHealthComponent>("HealthComponent");
}

void EUnitBase::BeginPlay()
{
	EEntity::BeginPlay();

	RegisterToScreenSelection(GetEntityManagerOwner());
}

FVector2D<int> EUnitBase::GetLocation()
{
	if (TransformComponent != nullptr)
	{
		return TransformComponent->GetLocationFinal();
	}

	return { };
}

FVector2D<int> EUnitBase::GetSize()
{
	if (RenderComponent != nullptr)
	{
		return TransformComponent->GetSize();
	}

	return { };
}

void EUnitBase::OnSelect()
{
	LOG_DEBUG("UnitBase selected");
}

void EUnitBase::OnDeSelect()
{
	LOG_DEBUG("UnitBase de-selected");
}
