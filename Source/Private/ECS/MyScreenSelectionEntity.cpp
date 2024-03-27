#include "GamePCH.h"
#include "ECS/MyScreenSelectionEntity.h"
#include "Input/EventHandler.h"

EMyScreenSelectionEntity::EMyScreenSelectionEntity(FEntityManager* InEntityManager)
	: EScreenSelectionEntity(InEntityManager)
{
}

void EMyScreenSelectionEntity::OnRightMouseButtonClicked(FVector2D<int> InLocation, EInputState InInputState)
{
	if (InInputState == EInputState::PRESS)
	{
		LastMouseLocation = InLocation;
	}
	else if (InInputState == EInputState::RELEASE)
	{
		if (LastMouseLocation == InLocation)
		{

		}
	}
}

void EMyScreenSelectionEntity::RegisterInput(const FEventHandler* InputHandler)
{
	EScreenSelectionEntity::RegisterInput(InputHandler);

	InputHandler->MouseDelegates.RightButton->Delegate.BindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}

void EMyScreenSelectionEntity::UnRegisterInput(const FEventHandler* InputHandler)
{
	EScreenSelectionEntity::UnRegisterInput(InputHandler);

	InputHandler->MouseDelegates.RightButton->Delegate.UnBindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}
