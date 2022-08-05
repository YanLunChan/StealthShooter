// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_Line.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, String);


void AGun_Line::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAutomatic() && !GetWorldTimerManager().IsTimerActive(timehandle) && activated) 
	{
		Execute_Shoot(this);
	}
}

void AGun_Line::Shoot_Implementation()
{
	fireCooldown = false;
	CreateLine();
	//add increment (needs to be seperate due to shotgun)
	AddIncrement();
	//add spread
	point = BulletSpread(UKismetMathLibrary::DegTan(current_theta) * range);
	chamber--;
	//set counter
	GetWorldTimerManager().SetTimer(timehandle, this, &AGun_Line::Cooldown, 1.0f, false, cooldownGun);
}

const TArray<AActor*> AGun_Line::CheckLine()
{
	//check if there's anything infront of the camera if there is then add that to the ignore actors (used for walls etc...)
	const FVector start = endPoint->GetComponentLocation();
	const FVector end = endPoint->GetComponentLocation() + (endPoint->GetForwardVector() * endPointOffset);
	const TArray<AActor*> ignoreActor = { endPoint->GetOwner() };
	FHitResult hitResult;
	const bool hit = UKismetSystemLibrary::LineTraceSingle(this, start, end, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ignoreActor, EDrawDebugTrace::None, hitResult, true,
		FLinearColor::Blue, FLinearColor::Yellow, 10.0f);
	if (!hit) 
	{
		return ignoreActor;
	}
	const TArray<AActor*> ignoreNewActor = { ignoreActor[0],hitResult.GetActor() };
	return ignoreNewActor;
}

void AGun_Line::CreateLine()
{
	//add linetrace here
	const FVector start = endPoint->GetComponentLocation();
	const FVector end = (endPoint->GetComponentLocation() + (endPoint->GetForwardVector() * range)) + (endPoint->GetRightVector() * point.X) + (endPoint->GetUpVector() * point.Y);
	FHitResult hitResult;
	const TArray<AActor*> ignoreActor = CheckLine();
	const bool hit = UKismetSystemLibrary::LineTraceSingle(this, start, end, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ignoreActor, EDrawDebugTrace::None, hitResult, true,
		FLinearColor::Red, FLinearColor::Green, 10.0f);
	FVector beamEnd = end;
	//if hit
	if (hit)
	{
		Damage(hitResult, damage);
		beamEnd = hitResult.Location;
	}
	//Spawn bullet tracer
	if (TracerEffect)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TracerEffect, MuzzleLocal->GetComponentLocation());
		NiagaraComp->SetNiagaraVariableVec3(FString("BeamEnd"), beamEnd);
	}
}

void AGun_Line::Damage(FHitResult hitresult, int value)
{
	if(hitresult.BoneName == "head")
	{
		hitresult.GetActor()->TakeDamage(999, FDamageEvent(UDamageType::StaticClass()), endPoint->GetOwner()->GetInstigatorController(), endPoint->GetOwner());
	}
	hitresult.GetActor()->TakeDamage(value, FDamageEvent(UDamageType::StaticClass()), endPoint->GetOwner()->GetInstigatorController(), endPoint->GetOwner());
}
