#include "GamePCH.h"
#include "ECS/UnitBase.h"

#include "Core/RTSAssetCollection.h"
#include "Core/RTSHUD.h"
#include "Core/GameModes/RTSGameMode.h"
#include "ECS/AI/AIActionAttack.h"
#include "ECS/AI/UnitAIMemorySet.h"
#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/Components/Collision/CircleCollisionComponent.h"
#include "ECS/Components/Collision/CollisionComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TargetingComponent.h"
#include "Engine/Logic/GameModeManager.h"
#include "UI/GameUserUI.h"

EUnitBase::EUnitBase(FEntityManager* InEntityManager)
	: EInteractableEntityBase(InEntityManager)
{
	TransformComponent = CreateComponent<UParentComponent>("TransformComponent");

	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");

	RenderComponent->SetImageSize({ 32, 32 });

	HealthComponent = TransformComponent->CreateComponent<UHealthComponent>("HealthComponent");
	MoveComponent = TransformComponent->CreateComponent<UMoveComponent>("MoveComponent");
	TargetingComponent = TransformComponent->CreateComponent<UTargetingComponent>("TargetingComponent");

	CollisionComponent = TransformComponent->CreateComponent<UCircleCollisionComponent>("CollisionComponent");
}

void EUnitBase::BeginPlay()
{
	Super::BeginPlay();

	const FAssetCollectionItem& Asset = GetUnitAsset();
	RenderComponent->SetImage(Asset.GetAssetName(), Asset.GetAssetPath());

	FEntityManager* EntityManagerOwner = GetEntityManagerOwner();
	Weapon = WeaponClass.Allocate(EntityManagerOwner);
	if (Weapon != nullptr)
	{
		EntityManagerOwner->RegisterNewEntity(Weapon);
		Weapon->AttachToEntity(this);
	}
}

void EUnitBase::SetupAIActions()
{
	Super::SetupAIActions();

	// Create AIMemorySet for AI Actions
	CreateAIMemorySet<FUnitAIMemorySet>();

	UnitAIMemorySetPtr = GetAIMemorySetByClass<FUnitAIMemorySet>();
	if (UnitAIMemorySetPtr)
	{
		UnitAIMemorySetPtr->ThisUnit = this;
		UnitAIMemorySetPtr->OnRandomHostileFound.BindObject(this, &EUnitBase::OnRandomHostileSelected);
	}

	// Hostile search tree
	FindHostile_AITree = CreateAiTree<FAITree>();
	FindHostile_AITree->CreateAction<FAIActionFindTarget>();

	// Create simple unit AI
	Movement_AITree = CreateAiTree<FAITree>();
	// Each unit depending on settings have different movement so it should be set on each unit class

	Attack_AITree = CreateAiTree<FAITree>();
	Attack_AITree->CreateAction<FAIActionAttack>();
}

FVector2D<int32> EUnitBase::GetLocation()
{
	if (TransformComponent != nullptr)
	{
		return TransformComponent->GetLocation();
	}

	return { };
}

FVector2D<int32> EUnitBase::GetSize()
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

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr && RTSGameMode->GetLocalController())
	{
		ERTSHUD* HUD = RTSGameMode->GetLocalController()->GetHUD<ERTSHUD>();
		if (HUD != nullptr)
		{
			FGameUserUI* UserUI = HUD->GetUserUI();
			if (UserUI != nullptr)
			{
				UserUI->AddUnit(this);
			}
		}
	}
}

void EUnitBase::OnDeSelect()
{
	LOG_DEBUG("UnitBase de-selected");

	FGameModeBase* CurrentGameMode = GetGameModeManager()->GetCurrentGameMode();
	FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(CurrentGameMode);
	if (RTSGameMode != nullptr && RTSGameMode->GetLocalController())
	{
		ERTSHUD* HUD = RTSGameMode->GetLocalController()->GetHUD<ERTSHUD>();
		if (HUD != nullptr)
		{
			FGameUserUI* UserUI = HUD->GetUserUI();
			if (UserUI != nullptr)
			{
				UserUI->RemoveUnit(this);
			}
		}
	}
}

void EUnitBase::OnDoAction(const FVector2D<int>& ActionLocation)
{
	Super::OnDoAction(ActionLocation);

	LOG_INFO("EUnitBase::OnDoAction@" << ActionLocation);

	MoveComponent->SetTargetMoveLocation(ActionLocation);
}

const FAssetCollectionItem& EUnitBase::GetUnitAsset()
{
	return RTSAssetCollection::UnitBase;
}

void EUnitBase::OnRandomHostileSelected(EEntity* InRandomHostileEntity)
{
	if (UnitAIMemorySetPtr != nullptr)
	{
		UnitAIMemorySetPtr->CurrentTarget = InRandomHostileEntity;
	}
}
