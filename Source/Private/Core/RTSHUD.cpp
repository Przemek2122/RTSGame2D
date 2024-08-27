#include "GamePCH.h"
#include "Core/RTSHUD.h"

#include "Engine/Logic/GameModeBase.h"

ERTSHUD::ERTSHUD(FEntityManager* InEntityManager)
	: EHUDBase(InEntityManager)
{
	FWindow* Window = GetWindow();

	UserUIPtr = FAutoUIMenu(new FGameUserUI(Window));
	PauseMenuPtr = FAutoUIMenu(new FGamePauseMenu(Window));
}

void ERTSHUD::BeginPlay()
{
	Super::BeginPlay();

	PauseMenuPtr->InitializePublic();

	FGameModeBase* GameMode = GetGameMode();
	if (GameMode != nullptr)
	{
		if (!GameMode->IsInProgress())
		{
			GameMode->OnGameplayStart.BindLambda([&]()
			{
				OnGameStart();
			});
		}
		else
		{
			OnGameStart();
		}
	}
}

void ERTSHUD::OnGameStart()
{
	UserUIPtr->InitializePublic();
}
