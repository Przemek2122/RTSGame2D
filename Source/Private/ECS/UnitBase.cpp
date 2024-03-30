#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/RenderComponent.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TransformComponent = CreateComponent<UBaseTransformComponent>("TransformComponent");
	TransformComponent->SetLocationFinal({ 140, 151 });

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");
	RenderComponent->SetImage("Unit", R"(Assets\Textures\Units\UnitBase.png)");
	RenderComponent->SetImageSize({ 32, 32 });

	HealthComponent = TransformComponent->CreateComponent<UHealthComponent>("HealthComponent");
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
		return TransformComponent->GetLocation();
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
