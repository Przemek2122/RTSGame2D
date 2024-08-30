#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"

#include "Core/RTSAssetCollection.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "UI/Widgets/FactoryUnitWidget.h"

FConstructionUnitData::FConstructionUnitData(const std::basic_string<char>& InName, FAssetCollectionItem InAssetCollectionItem)
	: Name(InName)
	, AssetCollectionItem(std::move(InAssetCollectionItem))
{
}

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ChildImageWidget(nullptr)
	, ContentHorizontalBoxWidget(nullptr)
{
}

void FFactoryWidget::Init()
{
	Super::Init();

	SetWidgetSize({ 1, 1 });

	CreateImageOfFactory();

	ContentHorizontalBoxWidget = CreateWidget<FHorizontalBoxWidget>();
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
	//ContentHorizontalBoxWidget->SetWidgetSizePercent({ 1, 1 });
	ContentHorizontalBoxWidget->SetScaleToContent(false);

	for (FConstructionUnitData& ConstructionUnitData : ConstructionUnitDataArray)
	{
		static const std::string Name = "UnitImage_";
		const std::string NameId = std::to_string(ConstructionUnitDataArray.Size());

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
