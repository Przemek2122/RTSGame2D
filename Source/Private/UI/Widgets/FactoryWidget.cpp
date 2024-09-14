#include "GamePCH.h"
#include "UI/Widgets/FactoryWidget.h"

#include "Core/RTSAssetCollection.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "UI/Widgets/FactoryUnitWidget.h"

FFactoryWidget::FFactoryWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FVerticalBoxWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, FactoryEntity(nullptr)
{
}

void FFactoryWidget::SetFactoryEntity(EUnitFactoryBase* InFactoryEntity)
{
	if (InFactoryEntity != nullptr)
	{
		FactoryEntity = InFactoryEntity;

		CreateConstructUnitList();

		CreateUnitsArray();
	}
	else
	{
		LOG_WARN("Missing factory pointer. Will not set factory enitity. UI will also NOT be created.");
	}
}

void FFactoryWidget::CreateUnitsArray()
{
	if (FactoryEntity != nullptr)
	{
		FVerticalBoxWidget* VerticalBoxNotes = CreateWidget<FVerticalBoxWidget>("FactoryWidget_VerticalBox_Notes");
		VerticalBoxNotes->SetScaleToContent(true);

		const std::string FactoryDisplayName = FactoryEntity->GetFactoryName();
		static const std::string ChooseUnitText = "Choose unit to build";

		FTextWidget* TextWidget1 = VerticalBoxNotes->CreateWidget<FTextWidget>("TextNote1");
		TextWidget1->SetText(FactoryDisplayName);

		FTextWidget* TextWidget2 = VerticalBoxNotes->CreateWidget<FTextWidget>("TextNote2");
		TextWidget2->SetText(ChooseUnitText);

		FHorizontalBoxWidget* ContentHorizontalBoxWidget = CreateWidget<FHorizontalBoxWidget>("FactoryWidget_HorizontalBox_Content");

		for (FVisualUnitData& ConstructionUnitData : ConstructionUnitDataArray)
		{
			static const std::string FactoryUnitText = "FactoryUnit_";
			const std::string FactoryUnitWidgetName = FactoryUnitText + ConstructionUnitData.Name;

			FButtonWidget* ButtonForUnit = ContentHorizontalBoxWidget->CreateWidget<FButtonWidget>();
			ButtonForUnit->SetScaleHorizontally(true);
			ButtonForUnit->OnLeftClickPress.BindLambda([&]()
			{
				LOG_DEBUG("Factory: Add unit of type: '" << ConstructionUnitData.Name << "'");

				FactoryEntity->AddUnitToQueue(ConstructionUnitData);
			});
			ButtonForUnit->OnRightClickPress.BindLambda([&]()
			{
				LOG_DEBUG("Factory: Remove unit of type: '" << ConstructionUnitData.Name << "'");

				FactoryEntity->RemoveUnitFromQueue(ConstructionUnitData);
			});

			FFactoryUnitWidget* FactoryUnitWidget = ButtonForUnit->CreateWidget<FFactoryUnitWidget>(FactoryUnitWidgetName);
			FactoryUnitWidget->SetUnitImage(ConstructionUnitData.AssetCollectionItem.GetAssetName(), ConstructionUnitData.AssetCollectionItem.GetAssetPath());
			FactoryUnitWidget->SetUnitName(ConstructionUnitData.Name);
		}
	}
	else
	{
		LOG_WARN("Missing factory pointer. Will not set factory UI.");
	}
}

void FFactoryWidget::CreateConstructUnitList()
{
	if (FactoryEntity != nullptr)
	{
		ConstructionUnitDataArray.Clear();

		ConstructionUnitDataArray = FactoryEntity->GetUnits();
	}
}
