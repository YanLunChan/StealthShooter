// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_Projectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
void AGun_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAutomatic() && !GetWorldTimerManager().IsTimerActive(timehandle) && activated)
	{

		Execute_Shoot(this);

	}
}

void AGun_Projectile::Shoot_Implementation()
{
	fireCooldown = false;
	chamber--;
	if(projectile != nullptr)
	{
		//(default number to make sure UI works properly)
		//might need to add variable for distance
		const FVector start = MuzzleLocal->GetComponentLocation();
		const FVector end = endPoint->GetComponentLocation() + (endPoint->GetForwardVector() * 1000.0f) + (endPoint->GetRightVector() * point.X) + (endPoint->GetUpVector() * point.Y);
		const FRotator rot = (end - start).Rotation();
		AActor* bullet = GetWorld()->SpawnActor<AActor>(projectile, MuzzleLocal->GetComponentLocation(), rot);
		bullet->SetOwner(this);
		groupedBullets.Add(bullet);

		//add increment (needs to be seperate due to shotgun)
		AddIncrement();
		//add spread
		point = BulletSpread(UKismetMathLibrary::DegTan(current_theta) * 1000.0f);

		GetWorldTimerManager().SetTimer(timehandle, this, &AGun_Projectile::Cooldown, 1.0f, false, cooldownGun);
	}
}
