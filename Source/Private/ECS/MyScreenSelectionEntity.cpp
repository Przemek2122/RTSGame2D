#include "GamePCH.h"
#include "ECS/MyScreenSelectionEntity.h"

#include "Input/WindowInputManager.h"

EMyScreenSelectionEntity::EMyScreenSelectionEntity(FEntityManager* InEntityManager)
	: EScreenSelectionEntity(InEntityManager)
{
}

bool EMyScreenSelectionEntity::OnRightMouseButtonClicked(FVector2D<int> InLocation, EInputState InInputState)
{
	bool bWasInputConsumed = false;

	if (InInputState == EInputState::PRESS)
	{
		LastMouseLocation = InLocation;

		bWasInputConsumed = true;
	}
	else if (InInputState == EInputState::RELEASE)
	{
		// Only if we do not move cursor after right click
		if (LastMouseLocation == InLocation)
		{

		}
	}

	return bWasInputConsumed;
}

void EMyScreenSelectionEntity::RegisterInput(FEventHandler* InputHandler)
{
	Super::RegisterInput(InputHandler);

	FWindowInputManager* WindowInputManager = GetWindow()->GetWindowInputManager();
	WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT")->Delegate.BindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}

void EMyScreenSelectionEntity::UnRegisterInput(FEventHandler* InputHandler)
{
	Super::UnRegisterInput(InputHandler);

	FWindowInputManager* WindowInputManager = GetWindow()->GetWindowInputManager();
	WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT")->Delegate.UnBindObject(this, &EMyScreenSelectionEntity::OnRightMouseButtonClicked);
}
