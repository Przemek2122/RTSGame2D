#include "GamePCH.h"
#include "UI/EditorUserUI.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapEditor.h"
#include "Renderer/Map/MapManager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"

FEditorUserUI::FEditorUserUI(FWindowAdvanced* InOwnerWindow)
	: FUIMenu(InOwnerWindow)
	, HorizontalBoxWidget(nullptr)
	, WholeScreenButtonWidget(nullptr)
	, MapEditor(nullptr)
{
}

void FEditorUserUI::GetAndCacheMapEditor()
{
	const FWindow* Window = GetOwnerWindow();
	if (Window != nullptr)
	{
		const FMapManager* MapManager = Window->GetMapManager();
		if (MapManager != nullptr)
		{
			MapEditor = MapManager->GetMapEditor();
		}
		else
		{
			LOG_ERROR("MapManager is nullptr");
		}
	}
	else
	{
		LOG_ERROR("Window is nullptr");
	}
}

void FEditorUserUI::Initialize()
{
	HorizontalBoxWidget = GetOwnerWindow()->CreateWidget<FHorizontalBoxWidget>();
	HorizontalBoxWidget->SetAnchor(EAnchor::BottomCenter);
	HorizontalBoxWidget->SetWidgetSizePercent(FVector2D(1.f, 0.1f));
	HorizontalBoxWidget->SetScaleToContent(true);

	FButtonWidget* SaveButtonWidget = HorizontalBoxWidget->CreateWidget<FButtonWidget>();
	SaveButtonWidget->OnClickRelease.BindObject(this, &FEditorUserUI::SaveMap);
	FTextWidget* TextWidget = SaveButtonWidget->CreateWidget<FTextWidget>();
	TextWidget->SetText("Save");

	CreateTextureWidgets();

	GetAndCacheMapEditor();

	WholeScreenButtonWidget = GetOwnerWindow()->CreateWidget<FButtonWidget>();
	WholeScreenButtonWidget->SetAnchor(EAnchor::TopCenter);
	WholeScreenButtonWidget->SetWidgetSizePercent(FVector2D(1.f, 0.9f));
	WholeScreenButtonWidget->SetWidgetVisibility(EWidgetVisibility::Hidden);
	WholeScreenButtonWidget->OnClickRelease.BindLambda([&]()
	{
		if (MapEditor != nullptr)
		{
			const FVector2D<int> MouseLocation = FButtonWidget::GetMouseLocation();

			LOG_DEBUG("Clicked ButtonWidget at " << MouseLocation.ToString());

			MapEditor->OnMapClicked(MouseLocation);
		}
		else
		{
			LOG_ERROR("MapEditor is nullptr");
		}
	});
}

void FEditorUserUI::DeInitialize()
{
	HorizontalBoxWidget->DestroyWidget();
	WholeScreenButtonWidget->DestroyWidget();
}

void FEditorUserUI::SaveMap()
{
	if (MapEditor != nullptr)
	{
		MapEditor->SaveMap();
	}
	else
	{
		LOG_ERROR("MapEditor is nullptr");
	}
}

void FEditorUserUI::CreateTextureWidgets()
{
	const FMapManager* MapManger = GetOwnerWindow()->GetMapManager();
	if (MapManger != nullptr)
	{
		const FMap* CurrentMap = MapManger->GetCurrentMap();
		if (CurrentMap != nullptr)
		{
			const FMapAsset* MapAsset = CurrentMap->GetMapAsset();
			if (MapAsset != nullptr && MapAsset->IsLoaded())
			{
				const FMapData& MapData = MapAsset->GetMapData();

				for (int i = 0; i < MapData.MapSubAssetSettingsArray.Size(); i++)
				{
					const FMapSubAssetSettings& MapSubAssetSettings = MapData.MapSubAssetSettingsArray[i];

					FButtonWidget* ButtonWidget = HorizontalBoxWidget->CreateWidget<FButtonWidget>();
					ButtonWidget->SetWidgetSize({ 40, 40 });

					FImageWidget* ImageWidget = ButtonWidget->CreateWidget<FImageWidget>();
					ImageWidget->SetImage(MapSubAssetSettings.TextureAssetPtr);
					ImageWidget->SetWidgetSize({ 32, 32 });

					ButtonWidget->OnClickRelease.BindLambda([&, i]()
					{
						if (MapEditor != nullptr)
						{
							MapEditor->SelectTileIndex(i);
						}
						else
						{
							LOG_ERROR("MapEditor is nullptr");
						}
					});
				}

				// @TODO Create scale to content on texture for HorizontalBoxWidget
			}
			else
			{
				LOG_ERROR("MapAsset is nullptr. Most likely it was not loaded.");
			}
		}
		else
		{
			LOG_ERROR("CurrentMap is nullptr. Most likely it was not loaded.");
		}
	}
	else
	{
		LOG_ERROR("MapManager is nullptr");
	}
}
