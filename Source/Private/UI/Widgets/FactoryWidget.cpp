#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"

#include "Core/RTSAssetCollection.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryUnitWidget.h"

FConstructionUnitData::FConstructionUnitData(const std::basic_string<char>& InName, FAssetCollectionItem InAssetCollectionItem)
	: Name(InName)
	, AssetCollectionItem(std::move(InAssetCollectionItem))
{
}

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
{
}

void FFactoryWidget::OpenUnitsConstructionMenu()
{
	CreateUnitsArray();
}

void FFactoryWidget::CreateUnitsArray()
{
	CArray<FConstructionUnitData> ConstructionUnitDataArray;
	ConstructUnitList(ConstructionUnitDataArray);

	FVerticalBoxWidget* VerticalBoxNotes = CreateWidget<FVerticalBoxWidget>("FactoryWidget_VerticalBox_Notes");
	VerticalBoxNotes->SetScaleToContent(true);

	const std::string FactoryDisplayName = GetFactoryDisplayName();
	static const std::string ChooseUnitText = "Choose unit to build";

	FTextWidget* TextWidget1 = VerticalBoxNotes->CreateWidget<FTextWidget>("TextNote1");
	TextWidget1->SetText(FactoryDisplayName);

	FTextWidget* TextWidget2 = VerticalBoxNotes->CreateWidget<FTextWidget>("TextNote2");
	TextWidget2->SetText(ChooseUnitText);

	FHorizontalBoxWidget* ContentHorizontalBoxWidget = CreateWidget<FHorizontalBoxWidget>("FactoryWidget_HorizontalBox_Content");

	for (FConstructionUnitData& ConstructionUnitData : ConstructionUnitDataArray)
	{
		static const std::string FactoryUnitWidgetName = "FactoryUnitWidget";

		FFactoryUnitWidget* FactoryUnitWidget = ContentHorizontalBoxWidget->CreateWidget<FFactoryUnitWidget>(FactoryUnitWidgetName);
		FactoryUnitWidget->SetUnitImage(ConstructionUnitData.AssetCollectionItem.GetAssetName(), ConstructionUnitData.AssetCollectionItem.GetAssetPath());
		FactoryUnitWidget->SetUnitName(ConstructionUnitData.Name);
	}
}

void FFactoryWidget::ConstructUnitList(CArray<FConstructionUnitData>& ConstructionUnitDataArray)
{
	FConstructionUnitData ConstructionUnitData("Base unit", RTSAssetCollection::UnitBase);

	ConstructionUnitDataArray.Push(ConstructionUnitData);
	ConstructionUnitDataArray.Push(ConstructionUnitData);
}

std::string FFactoryWidget::GetFactoryDisplayName() const
{
	static const std::string BaseFactoryDisplayName = "Base factory";

	return BaseFactoryDisplayName;
}
