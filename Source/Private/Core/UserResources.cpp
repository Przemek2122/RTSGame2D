// Created by Przemys³aw Wiewióra 2024

#include "GamePCH.h"
#include "Core/UserResources.h"

FResource::FResource(const int InitialAmount)
	: NumberOfResource(InitialAmount)
{
}

void FResource::Add(const int Amount)
{
	NumberOfResource += Amount;
}

void FResource::Subtract(const int Amount)
{
	NumberOfResource -= Amount;
}

void FResource::Set(const int Amount)
{
	NumberOfResource = Amount;
}

int FResource::Get() const
{
	return NumberOfResource;
}

FUserResources::FUserResources()
{
}
