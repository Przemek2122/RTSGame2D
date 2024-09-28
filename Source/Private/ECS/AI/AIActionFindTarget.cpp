#include "GamePCH.h"
#include "ECS/AI/AIActionFindTarget.h"

#include "ECS/Entity.h"
#include "ECS/Collision/BaseCollision.h"
#include "ECS/Collision/CollisionManager.h"
#include "ECS/Components/TeamComponent.h"
#include "ECS/Components/Collision/CollisionComponent.h"
#include "Timer/TimerManager.h"
#include "Threads/ThreadsManager.h"

FAIActionFindTarget::FAIActionFindTarget(FAITree* InAiTree)
	: FAIActionBase(InAiTree)
	, Entity(nullptr)
	, CollisionComponent(nullptr)
	, bIsActionReady(true)
	, bIsAsyncActionFinished(false)
	, ActionLockTime(0.7f)
{
}

void FAIActionFindTarget::Initialize()
{
	Super::Initialize();

	Entity = GetOwnerEntity();
	CollisionComponent = Entity->GetComponentByClass<UCollisionComponent>();
}

void FAIActionFindTarget::StartAction()
{
	Super::StartAction();

	bIsActionReady = false;
	bIsAsyncActionFinished = false;

	if (CollisionComponent != nullptr)
	{
		FDelegateSafe<> AsyncWork;
		AsyncWork.BindObject(this, &FAIActionFindTarget::IterateCollisionToFindHostiles);

		FDelegateSafe<> MainThreadCallback;
		MainThreadCallback.BindObject(this, &FAIActionFindTarget::OnCollisionIterationFinished);

		GEngine->GetThreadsManager()->AddAsyncDelegate(AsyncWork, MainThreadCallback);
	}
	else
	{
		LOG_WARN("Missing collision component, AIActionFindTarget will not work.");
	}
}

void FAIActionFindTarget::EndAction()
{
	Super::EndAction();

	ActionStartDelayTimer->PauseTimer();
	OnActionDelayFinished(nullptr);
}

bool FAIActionFindTarget::ShouldFinishAction() const
{
	return bIsAsyncActionFinished;
}

bool FAIActionFindTarget::IsActionReady() const
{
	return bIsActionReady;
}

void FAIActionFindTarget::SetUnlockActionTimer()
{
	FDelegateSafe<void, FOptionalTimerParams*> TimerDelegate;
	TimerDelegate.BindObject(this, &FAIActionFindTarget::OnActionDelayFinished);
	ActionStartDelayTimer = FTimerManager::CreateTimerSync(TimerDelegate, ActionLockTime);
}

void FAIActionFindTarget::IterateCollisionToFindHostiles()
{
	if (IsActionRunning())
	{
		HostileEntitiesFound.Clear();

		CArray<FCollisionBase*> CollisionObjectsArray = CollisionComponent->GetCollisionObjectsArray();
		for (FCollisionBase* ObjectsArray : CollisionObjectsArray)
		{
			const CArray<FCollisionTile*>& Tiles = ObjectsArray->GetCurrentlyLocatedTiles();
			if (Tiles.Size() > 0)
			{
				CheckCollisionTiles(Tiles);

				// Take only first collision with any tile
				break;
			}
		}
	}
}

void FAIActionFindTarget::CheckCollisionTiles(const CArray<FCollisionTile*> InCollisionTiles)
{
	for (FCollisionTile* CollisionTile : InCollisionTiles)
	{
		for (FCollisionBase* CollisionObject : CollisionTile->CollisionObjects)
		{
			EEntity* CollisionObjectEntity = CollisionObject->GetCollisionComponent()->GetEntity();
			if (CollisionObjectEntity != Entity)
			{
				UTeamComponent* EntityTeamComponent = Entity->GetComponentByClass<UTeamComponent>();
				if (EntityTeamComponent != nullptr)
				{
					UTeamComponent* OtherEntityTeamComponent = CollisionObjectEntity->GetComponentByClass<UTeamComponent>();
					if (OtherEntityTeamComponent != nullptr)
					{
						int32 ThisEntityTeam = EntityTeamComponent->GetCurrentTeam();
						int32 OtherEntityTeam = OtherEntityTeamComponent->GetCurrentTeam();

						if (ThisEntityTeam != OtherEntityTeam)
						{
							HostileEntitiesFound.Push(CollisionObjectEntity);
						}
					}
				}
			}
		}
	}
}

void FAIActionFindTarget::OnCollisionIterationFinished()
{
	if (HostileEntitiesFound.Size() > 0)
	{
		OnHostileEntitiesFound.Execute(HostileEntitiesFound);
	}

	bIsAsyncActionFinished = true;

	SetUnlockActionTimer();
}

void FAIActionFindTarget::OnActionDelayFinished(FOptionalTimerParams* OptionalTimerParams)
{
	bIsActionReady = true;
}