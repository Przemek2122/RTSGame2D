#pragma once

#include "CoreMinimal.h"
#include "ECS\Entities\ScreenSelectionEntity.h"

class EMyScreenSelectionEntity : public EScreenSelectionEntity
{
public:
	EMyScreenSelectionEntity(FEntityManager* InEntityManager);
	~EMyScreenSelectionEntity() override = default;

	void OnRightMouseButtonClicked(FVector2D<int> InLocation, EInputState InInputState);

protected:
	void RegisterInput(FEventHandler* InputHandler) override;
	void UnRegisterInput(FEventHandler* InputHandler) override;

protected:
	FVector2D<int> LastMouseLocation;

};
