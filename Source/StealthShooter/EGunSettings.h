// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGunSettings.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EGunSettings : uint8
{
	Semi UMETA(DisplayName = "Semi-Automatic"),
	Auto UMETA(DisplayName = "Automatic")
};
