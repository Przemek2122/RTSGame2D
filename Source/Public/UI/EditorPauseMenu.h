#pragma once

#include "CoreMinimal.h"
#include "Renderer\Widgets\UIMenu.h"

class FEditorPauseMenu : public FUIMenu
{
public:


protected:
	/** Begin FUIMenu */
	void Initialize() override;
	void DeInitialize() override;
	/** End FUIMenu */

};
