// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

/** Single resource class */
class FResource
{
public:
	FResource(const int InitialAmount = 0);

	void Add(const int Amount);
	void Subtract(const int Amount);

	void Set(const int Amount);
	int Get() const;

protected:
	int32 NumberOfResource;

};

/**
 * Class for containing user resources
 */
class FUserResources
{
public:
	FUserResources();

	/** Some basic resource (physical) required to build unit */
	FResource Metal;

	/** Resource (non-physical) */
	FResource Energy;
	
};
