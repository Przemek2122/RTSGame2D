// Created by Przemys�aw Wiewi�ra 2023

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
