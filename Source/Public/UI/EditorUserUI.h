// Created by Przemys³aw Wiewióra 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "Assets/Assets/MapAsset.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

class FButtonWidget;
class FMapEditor;
class FHorizontalBoxWidget;
class FWindowAdvanced;

class FEditorUserUI : public FUIMenu
{
public:
	FEditorUserUI(FWindowAdvanced* InOwnerWindow);
	void GetAndCacheMapEditor();

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

	void SaveMap();

protected:
	void CreateTextureWidgets();

protected:
	/** Container widget */
	FHorizontalBoxWidget* HorizontalBoxWidget;

	/** Current texture */
	FMapSubAssetSettings MapSubAssetSettingsSelected;

	/** Whole screen widget with low prio to capture click on map */
	FButtonWidget* ButtonWidget;

	/** Map editor cache */
	FMapEditor* MapEditor;

};
