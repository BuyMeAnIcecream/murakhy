// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "EDirection.generated.h"
#pragma once
/**
 * 
 */
UENUM(BlueprintType)
enum class EDirection : uint8
{
	ET_North UMETA(DisplayName = "North"),
	ET_NorthEast UMETA(DisplayName = "North-East"),
	ET_East UMETA(DisplayName = "East"),
	ET_SouthEast UMETA(DisplayName = "South-East"),
	ET_South UMETA(DisplayName = "South"),
	ET_SouthWest UMETA(DisplayName = "South-West"),
	ET_West UMETA(DisplayName = "West"),
	ET_NorthWest UMETA(DisplayName = "North-West"),
	ET_END
};