// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBaseClass.h"
#include "Components/BoxComponent.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, String);

// Sets default values
AGunBaseClass::AGunBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(GunMesh);
	//create muzzle location here
	MuzzleLocal = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocal->SetupAttachment(GunMesh);
	fireCooldown = true;
	MAX_THETA = 0;
	
	//create box collision
	obtainGun = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collision"));
	obtainGun->SetupAttachment(GunMesh);
}

void AGunBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (spreadCooldown != 0 && count < spreadCooldown)
	{
		current_theta = FMath::Lerp(lerpStart_theta, MIN_THETA, count / spreadCooldown);
		count += DeltaTime;
		return;

	}
	//incase lerp cause current_radius to end at 1 or 2 off
	current_theta = MIN_THETA;
	point = FVector2D::ZeroVector;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("x: %f y: %f"), point.X,point.Y));
}

void AGunBaseClass::SetSceneComponent(USceneComponent* sc, float distance)
{
	endPoint = sc;
	endPointOffset = distance;
	SetOwner(sc->GetOwner());
}

bool AGunBaseClass::IsAutomatic()
{
	return weaponSetting == EGunSettings::Auto;
}

void AGunBaseClass::Shoot_Implementation() {}

void AGunBaseClass::CanShoot_Implementation(bool pressed)
{
	activated = pressed;
}

void AGunBaseClass::Reload_Implementation(int amount)
{
	//check if full ammo
	if (chamber < MAX_CHAMBER) 
	{
		if (reserve < amount) 
		{
			chamber = reserve;
			reserve = 0;
		}
		else 
		{
			reserve -= amount;
			chamber += amount;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Reserve: %i, Chamber: %i"), reserve, chamber));

	}
}

// Called when the game starts or when spawned
void AGunBaseClass::BeginPlay()
{
	Super::BeginPlay();
	count = spreadCooldown;
	chamber = MAX_CHAMBER;
	reserve = MAX_RESERVE;
	current_theta = MIN_THETA;
}

FVector2D AGunBaseClass::BulletSpread(float radius)
{
	PrintString(FVector2D(current_theta, radius).ToString());
	//find random number between 0-360
	const float angle = FMath::RandRange(0.0f, 360.0f);
	const float distance = FMath::RandRange(0.0f, radius);
	const float x = FMath::Cos(angle * (PI/180));
	const float y = FMath::Sin(angle * (PI / 180));
	lerpStart_theta = FMath::Clamp(current_theta, MIN_THETA, MAX_THETA);
	count = 0;
	return FVector2D(x * distance, y * distance);
}

void AGunBaseClass::AddIncrement()
{
	current_theta += increment_theta;
	
}

void AGunBaseClass::Cooldown()
{
	fireCooldown = true;
	GetWorldTimerManager().ClearTimer(timehandle);
}
