// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Kismet/KismetMathLibrary.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, String);

void AShotgun::Shoot_Implementation()
{
	fireCooldown = false;
	AddIncrement();
	for (int i = 0; i < pellets; i++) 
	{
		CreateLine();
		point = BulletSpread(UKismetMathLibrary::DegTan(current_theta) * range);
	}
	chamber--;
	

	GetWorldTimerManager().SetTimer(timehandle, this, &AGun_Line::Cooldown, 1.0f, false, cooldownGun);
}

void AShotgun::Damage(FHitResult hitresult, int value)
{
	hitresult.GetActor()->TakeDamage(value, FDamageEvent(UDamageType::StaticClass()), endPoint->GetOwner()->GetInstigatorController(), endPoint->GetOwner());
}
