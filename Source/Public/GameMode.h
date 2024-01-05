// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"

class FGameMode
{
public:
	FGameMode(FWindow* InWindow);

	void StartGame();
	void EndGame();

protected:
	FWindow* Window;
	
};
