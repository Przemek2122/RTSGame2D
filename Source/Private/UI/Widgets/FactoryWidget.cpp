#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"

#include "Core/RTSAssetCollection.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryUnitWidget.h"

FConstructionUnitData::FConstructionUnitData(const std::basic_string<char>& InName, FAssetCollectionItem InAssetCollectionItem)
	: Name(InName)
	, AssetCollectionItem(std::move(InAssetCollectionItem))
{
}

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ChildImageWidget(nullptr)
	, ContentHorizontalBoxWidget(nullptr)
{
}

void FFactoryWidget::Init()
{
	Super::Init();

	CreateImageOfFactory();

	ContentHorizontalBoxWidget = CreateWidget<FHorizontalBoxWidget>();

#if WIDGET_DEBUG_COLORS
	SetWidgetDebugColor(FColorRGBA::ColorLightGreen());
#endif
}

void FFactoryWidget::SetFactoryImage(const std::string& InFactoryImageName, const std::string& InFactoryImagePath) const
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

	ContentHorizontalBoxWidget->ClearChildren();

	FTextWidget* TextWidget1 = ContentHorizontalBoxWidget->CreateWidget<FTextWidget>();
	TextWidget1->SetText(GetFactoryDisplayName());

	static const std::string ChooseUnitText = "Choose unit to build";

	FTextWidget* TextWidget2 = ContentHorizontalBoxWidget->CreateWidget<FTextWidget>();
	TextWidget2->SetText(ChooseUnitText);

	for (FConstructionUnitData& ConstructionUnitData : ConstructionUnitDataArray)
	{
		FFactoryUnitWidget* FactoryUnitWidget = ContentHorizontalBoxWidget->CreateWidget<FFactoryUnitWidget>();
		FactoryUnitWidget->SetUnitImage(ConstructionUnitData.AssetCollectionItem.GetAssetName(), ConstructionUnitData.AssetCollectionItem.GetAssetPath());
		FactoryUnitWidget->SetUnitName(ConstructionUnitData.Name);
	}
}

void FFactoryWidget::CreateImageOfFactory()
{
	ChildImageWidget = CreateWidget<FImageWidget>();
}

void FFactoryWidget::ConstructUnitList(CArray<FConstructionUnitData>& ConstructionUnitDataArray)
{
	FConstructionUnitData ConstructionUnitData("Base unit", RTSAssetCollection::UnitBase);

	ConstructionUnitDataArray.Push(ConstructionUnitData);
}

std::string FFactoryWidget::GetFactoryDisplayName() const
{
	static const std::string BaseFactoryDisplayName = "Base factory";

	return BaseFactoryDisplayName;
}
