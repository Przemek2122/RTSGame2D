#include "GamePCH.h"
#include "UI/GameUserUI.h"

#include "ECS/UnitBase.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryWidget.h"
#include "UI/Widgets/UnitWidget.h"

FGameUserUI::FGameUserUI(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, MainHorizontalBox(nullptr)
	, CurrentlyCreatedFactories(0)
	, CurrentlyCreatedUnits(0)
	, CurrentSelectionType(ECurrentSelectionType::None)
{
	RegisterTickInterface();
}

ETickPhase FGameUserUI::GetTickPhase() const
{
	return ETickPhase::Default;
}

void FGameUserUI::Tick(float DeltaTime)
{
	bool bAnyChanged = false;

	// Update if changed
	const int SelectedUnitsSize = SelectedUnits.Size();
	if (CurrentlyCreatedUnits != SelectedUnitsSize)
	{
		UpdateOnSelectedUnitsChange();

		bAnyChanged = true;
	}

	// Update if changed
	const int SelectedFactoriesSize = SelectedFactories.Size();
	if (CurrentlyCreatedFactories != SelectedFactoriesSize)
	{
		UpdateOnSelectedFactoriesChanged();

		bAnyChanged = true;
	}

	// In case of no selected factories or units
	if (bAnyChanged && (SelectedFactoriesSize == 0 && SelectedUnitsSize == 0))
	{
		ResetSelection();
	}
}

void FGameUserUI::AddFactoryBase(EUnitFactoryBase* InFactoryBase)
{
	bool bShouldAddFactory = false;

	// If already selecting factories
	if (CurrentSelectionType == ECurrentSelectionType::Factories)
	{
		bShouldAddFactory = true;
	}
	// Or if not selecting anything yet
	else if (CurrentSelectionType == ECurrentSelectionType::None)
	{
		CurrentSelectionType = ECurrentSelectionType::Factories;

		bShouldAddFactory = true;
	}

	if (bShouldAddFactory)
	{
		SelectedFactories.Push(InFactoryBase);
	}
}

void FGameUserUI::AddUnitBase(EUnitBase* InUnitBase)
{
	bool bShouldAddUnit = false;

	// If already selecting units
	if (CurrentSelectionType == ECurrentSelectionType::Units)
	{
		bShouldAddUnit = true;
	}
	// Or if not selecting anything yet
	else if (CurrentSelectionType == ECurrentSelectionType::None)
	{
		CurrentSelectionType = ECurrentSelectionType::Units;

		bShouldAddUnit = true;
	}

	if (bShouldAddUnit)
	{
		SelectedUnits.Push(InUnitBase);
	}
}

void FGameUserUI::RemoveFactoryBase(EUnitFactoryBase* InFactoryBase)
{
	SelectedFactories.Remove(InFactoryBase);
}

void FGameUserUI::RemoveUnitBase(EUnitBase* InUnitBase)
{
	SelectedUnits.Remove(InUnitBase);
}

void FGameUserUI::Initialize()
{
	MainHorizontalBox = GetOwnerWindow()->CreateWidget<FHorizontalBoxWidget>();
	MainHorizontalBox->SetAnchor(EAnchor::BottomCenter);
	MainHorizontalBox->SetWidgetSizePercent({ 1.f, 0.25f });

	CreateDefaultWidget();
}

void FGameUserUI::DeInitialize()
{
	MainHorizontalBox->DestroyWidget();
}

void FGameUserUI::UpdateOnSelectedUnitsChange()
{
	CurrentlyCreatedUnits = 0;

	MainHorizontalBox->ClearChildren();

	for (EUnitBase* SelectedUnit : SelectedUnits)
	{
		CurrentlyCreatedUnits++;

		const FUnitWidget* UnitWidget = MainHorizontalBox->CreateWidget<FUnitWidget>();
		FAssetCollectionItem UnitAsset = SelectedUnit->GetUnitAsset();
		UnitWidget->SetFactoryImage(UnitAsset.GetAssetName(), UnitAsset.GetAssetPath());
	}

	LOG_INFO("SelectedUnits: " << SelectedUnits.Size());
}

void FGameUserUI::UpdateOnSelectedFactoriesChanged()
{
	CurrentlyCreatedFactories = 0;

	MainHorizontalBox->ClearChildren();

	for (EUnitFactoryBase* SelectedFactory : SelectedFactories)
	{
		CurrentlyCreatedFactories++;

		const FFactoryWidget* FactoryWidget = MainHorizontalBox->CreateWidget<FFactoryWidget>();

		FAssetCollectionItem FactoryAsset = SelectedFactory->GetFactoryAsset();
		FactoryWidget->SetFactoryImage(FactoryAsset.GetAssetName(), FactoryAsset.GetAssetPath());
	}
}

void FGameUserUI::ResetSelection()
{
	MainHorizontalBox->ClearChildren();

	CurrentSelectionType = ECurrentSelectionType::None;

	CreateDefaultWidget();
}

void FGameUserUI::CreateDefaultWidget()
{
	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("No factory or unit selected.");
}
