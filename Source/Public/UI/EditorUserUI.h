// Created by Przemys³aw Wiewióra 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "Assets/Assets/MapAsset.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

class FHorizontalBoxWidget;
class FWindowAdvanced;

class FEditorUserUI : public FUIMenu
{
public:
	FEditorUserUI(FWindowAdvanced* InOwnerWindow);

protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

protected:
	void CreateTextureWidgets();

protected:
	/** Container widget */
	FHorizontalBoxWidget* HorizontalBoxWidget;

	/** Current texture */
	FMapSubAssetSettings MapSubAssetSettingsSelected;

};
