// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, String);

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	defaultHealth = 100;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	health = defaultHealth;
	// ...
	
}

void UHealthComponent::TakeDamage(AActor* damagedActor, float damage, const UDamageType* type, AController* intigater, AActor* damageCauser)
{
	if (damage <= 0)
		return;
	health = FMath::Clamp((health - damage), 0.0f, defaultHealth);

	PrintString("called");
}


