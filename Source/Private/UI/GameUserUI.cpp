#include "GamePCH.h"
#include "UI/GameUserUI.h"

#include "ECS/UnitBase.h"
#include "Renderer/Widgets/Samples/BorderWidget.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryWidget.h"
#include "UI/Widgets/UnitWidget.h"

FGameUserUI::FGameUserUI(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
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

void FGameUserUI::AddFactory(EUnitFactoryBase* InFactoryBase)
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

void FGameUserUI::AddUnit(EUnitBase* InUnitBase)
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

void FGameUserUI::RemoveFactory(EUnitFactoryBase* InFactoryBase)
{
	SelectedFactories.Remove(InFactoryBase);
}

void FGameUserUI::RemoveUnit(EUnitBase* InUnitBase)
{
	SelectedUnits.Remove(InUnitBase);
}

void FGameUserUI::Initialize()
{
	BorderContent = GetOwnerWindow()->CreateWidget<FBorderWidget>("FactoryWidget_Border_Content");
	BorderContent->SetColor(FColorRGBA(50, 39, 245, 1));
	BorderContent->SetBorderDisplayMethod(EBorderDisplayMethod::BorderWithFill);
	BorderContent->SetAnchor(EAnchor::BottomCenter);
	BorderContent->SetWidgetSizePercent({ 1.f, 0.25f });

	CreateDefaultWidget();
}

void FGameUserUI::DeInitialize()
{
	BorderContent->DestroyWidget();
}

void FGameUserUI::UpdateOnSelectedUnitsChange()
{
	CurrentlyCreatedUnits = 0;

	BorderContent->ClearChildren();

	for (EUnitBase* SelectedUnit : SelectedUnits)
	{
		CurrentlyCreatedUnits++;

		const FUnitWidget* UnitWidget = BorderContent->CreateWidget<FUnitWidget>();
		FAssetCollectionItem UnitAsset = SelectedUnit->GetUnitAsset();
		UnitWidget->SetFactoryImage(UnitAsset.GetAssetName(), UnitAsset.GetAssetPath());
	}

	LOG_INFO("SelectedUnits: " << SelectedUnits.Size());
}

void FGameUserUI::UpdateOnSelectedFactoriesChanged()
{
	static const std::string GameUI_FactoryWidget = "FactoryWidget_GameUI";

	CurrentlyCreatedFactories = 0;

	BorderContent->ClearChildren();

	if (SelectedFactories.Size() == 1)
	{
		CurrentlyCreatedFactories++;

		EUnitFactoryBase* SelectedFactory = SelectedFactories[0];

		FFactoryWidget* FactoryWidget = BorderContent->CreateWidget<FFactoryWidget>(GameUI_FactoryWidget);
		FactoryWidget->OpenUnitsConstructionMenu();
	}
	else
	{
		for (EUnitFactoryBase* SelectedFactory : SelectedFactories)
		{
			CurrentlyCreatedFactories++;

			FAssetCollectionItem FactoryAsset = SelectedFactory->GetFactoryAsset();

			// @TODO This section does nothing now, we need new widget for multiple factories
		}
	}
}

void FGameUserUI::ResetSelection()
{
	BorderContent->ClearChildren();

	CurrentSelectionType = ECurrentSelectionType::None;

	CreateDefaultWidget();
}

void FGameUserUI::CreateDefaultWidget()
{
	static const std::string WidgetName = "Text_GameUI_NoFactoryOrUnit";
	static const std::string NoFactoryOrUnitSelectedText = "No factory or unit selected.";

	BorderContent->CreateWidget<FTextWidget>(WidgetName)->SetText(NoFactoryOrUnitSelectedText);
}
