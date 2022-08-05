// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EWeapon.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum EWeapon
{
	Hold_None	 UMETA(DisplayName = "None"),
	Hold_Pistol	 UMETA(DisplayName = "Pistol"),
	Hold_Rifle	 UMETA(DisplayName = "Rifle"),
	Hold_ShotGun UMETA(DisplayName = "ShotGun")
};
