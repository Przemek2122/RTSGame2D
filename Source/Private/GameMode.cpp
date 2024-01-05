// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "GameMode.h"

#include "Renderer/Map/Mapmanager.h"

FGameMode::FGameMode(FWindow* InWindow)
	: Window(InWindow)
{
}

void FGameMode::StartGame()
{
	FMapManager* MapsManager = Window->GetMapManager();
	if (MapsManager != nullptr)
	{
		MapsManager->CacheAvailableMaps();
		CArray<std::string> Maps = MapsManager->GetAvailableMaps();
		for (std::string& Map : Maps)
		{
			MapsManager->LoadMap(Map);

			break;
		}

	}
}

void FGameMode::EndGame()
{
}
