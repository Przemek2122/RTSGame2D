// Created by Przemys³aw Wiewióra 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "Renderer/Widgets/UIMenu.h"

class FEditoruUserUI : public FUIMenu
{
public:


protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

};
