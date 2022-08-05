// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBaseClass.h"
#include "Gun_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSHOOTER_API AGun_Projectile : public AGunBaseClass
{
	GENERATED_BODY()
	
	public:

	virtual void Tick(float DeltaTime) override;
	//interface goes here
	virtual void Shoot_Implementation() override;

	UPROPERTY(BlueprintReadWrite, Category = "Grouped Bullets")
	TArray<AActor*> groupedBullets;
	protected:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> projectile;
};
