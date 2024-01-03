// Main project class

#pragma once

#include "GamePCH.h"
#include "Core/ShooterGameEngine.h"

inline FEngineManager EngineManager;

inline int StartEngine(const int Argc = 0, char* Argv[] = nullptr) // const int Argc, char* Argv[]
{
	EngineManager.Start<FShooterGameEngine>(Argc, Argv);
	
    return 0;
}

// Could be start point to engine if this project was used to produce exe
int main(const int Argc, char* Argv[])
{
	StartEngine(Argc, Argv);
}
