// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun_Line.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSHOOTER_API AShotgun : public AGun_Line
{
	GENERATED_BODY()
	
	public:
	virtual void Shoot_Implementation() override;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int pellets;

	virtual void Damage(FHitResult hitresult, int value);
};
