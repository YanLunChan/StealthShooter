// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBaseClass.h"
#include "Gun_Line.generated.h"

class UNiagaraSystem;

UCLASS()
class STEALTHSHOOTER_API AGun_Line : public AGunBaseClass
{
	GENERATED_BODY()
	
	public:

	virtual void Tick(float DeltaTime) override;
	//interface goes here
	virtual void Shoot_Implementation() override;

	protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float range;
	
	const TArray<AActor*> CheckLine();
	void CreateLine();
	virtual void Damage(FHitResult hitresult, int value);

	UPROPERTY(EditAnywhere, Category = "Niagara")
		UNiagaraSystem* TracerEffect;
};
