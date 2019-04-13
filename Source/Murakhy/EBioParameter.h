// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EBioParameter.generated.h"
#pragma once

UENUM(BlueprintType)
enum class EBioParameter : uint8
{
	EBP_Food UMETA(DisplayName = "Food"),
	EBP_Dna UMETA(DisplayName = "DNA"),
	EBP_Light UMETA(DisplayName = "Light"),
	EBP_END
};

