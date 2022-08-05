 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Traps.generated.h"

class UBoxComponent;

UCLASS()
class STEALTHSHOOTER_API ATraps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	bool attack = false;

	UPROPERTY(VisibleAnywhere, Category = "Activation")
	UBoxComponent* activation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activation CoolDown")
	float delay;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
