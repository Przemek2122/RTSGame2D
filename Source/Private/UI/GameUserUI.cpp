#include "GamePCH.h"
#include "UI/GameUserUI.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryWidget.h"

FGameUserUI::FGameUserUI(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, MainHorizontalBox(nullptr)
	, CurrentlyCreatedFactories(0)
	, CurrentlyCreatedUnits(0)
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
	const int SelectedFactoriesSize = SelectedFactories.Size();
	if (CurrentlyCreatedFactories != SelectedFactoriesSize)
	{
		UpdateOnSelectedFactoriesChanged();

		bAnyChanged = true;
	}

	// Update if changed
	const int SelectedUnitsSize = SelectedUnits.Size();
	if (CurrentlyCreatedUnits != SelectedUnitsSize)
	{
		//UpdateOnSelectedUnitsChange();

		bAnyChanged = true;
	}

	// In case of no selected factories or units
	if (bAnyChanged && (SelectedFactoriesSize == 0 && SelectedUnitsSize == 0))
	{
		CreateDefaultWidget();
	}
}

void FGameUserUI::AddFactoryBase(EUnitFactoryBase* InFactoryBase)
{
	SelectedFactories.Push(InFactoryBase);
}

void FGameUserUI::AddUnitBase(EUnitBase* InUnitBase)
{
	SelectedUnits.Push(InUnitBase);
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


	}
}

void FGameUserUI::UpdateOnSelectedFactoriesChanged()
{
	CurrentlyCreatedFactories = 0;

	MainHorizontalBox->ClearChildren();

	for (EUnitFactoryBase* SelectedFactory : SelectedFactories)
	{
		CurrentlyCreatedFactories++;

		const FFactoryWidget* FactoryWidget = MainHorizontalBox->CreateWidget<FFactoryWidget>();

		FactoryWidget->SetFactoryDisplayName(SelectedFactory->GetFactoryDisplayName());

		FRTSAsset FactoryAsset = SelectedFactory->GetFactoryAsset();
		FactoryWidget->SetFactoryImage(FactoryAsset.GetAssetName(), FactoryAsset.GetAssetPath());
	}
}

void FGameUserUI::CreateDefaultWidget()
{
	MainHorizontalBox->ClearChildren();

	MainHorizontalBox->CreateWidget<FTextWidget>()->SetText("No factory or unit selected.");
}
