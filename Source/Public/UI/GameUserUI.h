#pragma once

#include "CoreMinimal.h"
#include "ECS/UnitFactoryBase.h"
#include "Interfaces/CoreLoop/ITickInterface.h"
#include "Renderer/Widgets/UIMenu.h"

class EUnitBase;

enum class ECurrentSelectionType
{
	None,
	Factories,
	Units,
};

class FGameUserUI : public FUIMenu, public ITickInterface
{
public:
	FGameUserUI(FWindow* InGameWindow);

	/** Begin ITickInterface */
	ETickPhase GetTickPhase() const override;
	void Tick(float DeltaTime) override;
	/** End ITickInterface */

	void AddFactory(EUnitFactoryBase* InFactoryBase);
	void AddUnit(EUnitBase* InUnitBase);

	void RemoveFactory(EUnitFactoryBase* InFactoryBase);
	void RemoveUnit(EUnitBase* InUnitBase);

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

	void UpdateOnSelectedUnitsChange();
	void UpdateOnSelectedFactoriesChanged();

	void ResetSelection();
	void CreateDefaultWidget();

protected:
	FBorderWidget* BorderContent;
	FHorizontalBoxWidget* HorizontalBoxWidget_Content;

	CArray<EUnitFactoryBase*> SelectedFactories;
	CArray<EUnitBase*> SelectedUnits;

	/** Number of currently created factories on UI */
	int CurrentlyCreatedFactories;

	/** Number of currently created units on UI */
	int CurrentlyCreatedUnits;

	ECurrentSelectionType CurrentSelectionType;

};
