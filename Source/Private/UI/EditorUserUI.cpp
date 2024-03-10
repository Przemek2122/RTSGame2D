#include "GamePCH.h"
#include "UI/EditorUserUI.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"

FEditorUserUI::FEditorUserUI(FWindowAdvanced* InOwnerWindow)
	: FUIMenu(InOwnerWindow)
	, HorizontalBoxWidget(nullptr)
{
}

void FEditorUserUI::Initialize()
{
	HorizontalBoxWidget = GetOwnerWindow()->CreateWidget<FHorizontalBoxWidget>();
	HorizontalBoxWidget->SetAnchor(EAnchor::BottomCenter);
	HorizontalBoxWidget->SetWidgetSizePercent(FVector2D(1.f, 0.1f));

	CreateTextureWidgets();
}

void FEditorUserUI::DeInitialize()
{
	HorizontalBoxWidget->DestroyWidget();
}

void FEditorUserUI::CreateTextureWidgets()
{
	const FMapManager* MapManger = GetOwnerWindow()->GetMapManager();
	if (MapManger != nullptr)
	{
		const FMap* CurrentMap = MapManger->GetCurrentMap();
		if (CurrentMap != nullptr)
		{
			FMapAsset* MapAsset = CurrentMap->GetMapAsset();
			if (MapAsset != nullptr && MapAsset->IsLoaded())
			{
				const FMapData& MapData = MapAsset->GetMapData();

				for (const FMapSubAssetSettings& MapSubAssetSettingsArray : MapData.MapSubAssetSettingsArray)
				{
					FImageWidget* ImageWidget = HorizontalBoxWidget->CreateWidget<FImageWidget>();
					ImageWidget->SetImage(MapSubAssetSettingsArray.TextureAssetPtr);



				}
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
