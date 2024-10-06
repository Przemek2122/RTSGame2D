#include "GamePCH.h"
#include "ECS/Weapons/WeaponMele.h"

#include "Core/RTSAssetCollection.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/Collision/SquareCollisionComponent.h"

EWeaponMelee::EWeaponMelee(FEntityManager* InEntityManager)
	: EWeapon(InEntityManager)
	, bIsAttacking(false)
	, WeaponPushTime(0)
	, WeaponReturnTime(0)
	, AttackStartTime(0)
	, AttackRelativeSpearOffset(0, -15)
{
	SetAttackCooldown(0.6f);

	URenderComponent* RenderComponent = GetRenderComponent();
	AttackSquareCollision = RenderComponent->CreateComponent<USquareCollisionComponent>("AttackSquareCollision");
	AttackSquareCollision->SetTransformFollowMethod(ETransformFollowMethod::RotateAroundParent);
	AttackSquareCollision->SetLocation({ 12, 0 });
	AttackSquareCollision->SetSize({ 4, 4 });
}

void EWeaponMelee::BeginPlay()
{
	Super::BeginPlay();

	StartingRelativeLocationOfSpear = GetRelativeLocation();
}

void EWeaponMelee::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttacking)
	{
		if (FUtil::IsDelayed(AttackStartTime, WeaponPushTime))
		{
			if (FUtil::IsDelayed(AttackStartTime, WeaponReturnTime))
			{
				bIsAttacking = false;

				SetRelativeLocation(StartingRelativeLocationOfSpear);
			}
			else
			{
				const float AttackPercent = FUtil::GetDelayPercent(AttackStartTime, WeaponReturnTime);
				const float AttackPercentMinusOne = 1 - AttackPercent; // -1 to run backwards

				// Back spear into starting position
				SetRelativeLocation(StartingRelativeLocationOfSpear + (AttackPercentMinusOne * FVector2D<float>(AttackRelativeSpearOffset)));
			}
		}
		else
		{
			const float AttackPercent = FUtil::GetDelayPercent(AttackStartTime, WeaponPushTime);

			// Move spear forward
			SetRelativeLocation(StartingRelativeLocationOfSpear + (AttackPercent * FVector2D<float>(AttackRelativeSpearOffset)));
		}
	}
}

FAssetCollectionItem EWeaponMelee::GetWeaponTexture() const
{
	return RTSAssetCollection::SpearWeapon;
}

void EWeaponMelee::PerformAttack()
{
	Super::PerformAttack();

	bIsAttacking = true;

	const float DelayBetweenAttacksTime = GetAttackCooldown();
	const float HalfDelayBetweenAttacksTime = DelayBetweenAttacksTime / 2;

	FUtil::StartDelay(AttackStartTime);

	WeaponPushTime = FUtil::SecondToMilliSecond(HalfDelayBetweenAttacksTime);
	WeaponReturnTime = FUtil::SecondToMilliSecond(DelayBetweenAttacksTime);
}

void EWeaponMelee::OnAttackDelayFinished()
{
	Super::OnAttackDelayFinished();

	bIsAttacking = false;
}
