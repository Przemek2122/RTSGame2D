// Created by Przemys³aw Wiewióra 2023

#include "GamePCH.h"
#include "GameMode.h"

#include "Renderer/Map/Mapmanager.h"

FGameMode::FGameMode(FWindow* InWindow)
	: Window(InWindow)
{
}

void FGameMode::OpenGameMapSelection()
{
}

void FGameMode::OpenEditorMapSelection()
{
	FMapManager* MapsManager = Window->GetMapManager();
	if (MapsManager != nullptr)
	{
		MapsManager->CacheAvailableMaps();
		CArray<std::string> Maps = MapsManager->GetAvailableMaps();

		// Primitve contains
		for (std::string& Map : Maps)
		{
			if (Map == "test_1")
			{
				MapsManager->LoadMap(Map);

				break;
			}
		}
	}
}

void FGameMode::StartGame()
{
}

void FGameMode::EndGame()
{
}
