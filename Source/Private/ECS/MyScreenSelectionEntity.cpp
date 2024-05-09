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
		// Only if we do not move cursor after right click
		if (LastMouseLocation == InLocation)
		{

		}
	}
}

void EMyScreenSelectionEntity::RegisterInput(FEventHandler* InputHandler)
{
	EScreenSelectionEntity::RegisterInput(InputHandler);

	InputHandler->MouseDelegates.GetMouseDelegateByName("RightButton")->Delegate.BindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}

void EMyScreenSelectionEntity::UnRegisterInput(FEventHandler* InputHandler)
{
	EScreenSelectionEntity::UnRegisterInput(InputHandler);

	InputHandler->MouseDelegates.GetMouseDelegateByName("RightButton")->Delegate.UnBindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}
