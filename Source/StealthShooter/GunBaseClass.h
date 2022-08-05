// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Shootable.h"
#include "EGunSettings.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBaseClass.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class EWeapon;

//delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpgradable);

UCLASS()
class STEALTHSHOOTER_API AGunBaseClass : public AActor, public IShootable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBaseClass();

	virtual void Tick(float DeltaTime) override;

	//check if weapon is automatic or semi automatic if so then act accourdingly
	bool IsAutomatic();
	//interface here (if remove error might occure)
	virtual void Shoot_Implementation();
	virtual void CanShoot_Implementation(bool pressed);
	virtual void Reload_Implementation(int amount);
	//set where bullet goes here
	UFUNCTION(BlueprintCallable)
	void SetSceneComponent(USceneComponent* sc, float distance);
	float endPointOffset;
	//gun marker goes here
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	USceneComponent* MuzzleLocal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* GunMesh;
	UFUNCTION(BlueprintCallable)
	void Cooldown();

	//delegate
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "EventDispatcher")
		FUpgradable Upgrade;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//create variables for all guns not shown in editor
	USceneComponent* endPoint;
	bool activated = false;
	
	//variables for base gun that needs properties/ can modify in blueprint
	UPROPERTY(BlueprintReadOnly)
	int chamber;
	UPROPERTY(BlueprintReadOnly)
	int reserve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MAX_RESERVE = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MAX_CHAMBER = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float cooldownGun = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float noise = 3.0f;
	
	//Spread

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MAX_THETA = 0;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	float MIN_THETA = 0;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	float increment_theta = 0;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	float spreadCooldown = 1;
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	float current_theta;
	float lerpStart_theta = 0;
	float count = 0;
	FVector2D point = FVector2D::ZeroVector;
	FVector2D BulletSpread(float radius);
	void AddIncrement();
	//cooldown timer functions
	UPROPERTY(BlueprintReadOnly, Category = "Reloading")
	bool fireCooldown = true;

	FTimerHandle timehandle;

	//Gun Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	TEnumAsByte<EWeapon> holdType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	EGunSettings weaponSetting = EGunSettings::Semi;

	//Pickup Settigns
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	UBoxComponent* obtainGun;

};
