// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SD_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHDEMO_API USD_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USD_HealthComponent();

	UFUNCTION(BlueprintCallable)
	float SetMaxHealth(float NewMaxHp) { MaxHealth = NewMaxHp; return MaxHealth; };

	UFUNCTION(BlueprintCallable)
	float SetHealth(float healthAdd);

	UFUNCTION(BlueprintCallable)
	float GetHealth() { return CurrentHealth; };

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return CurrentHealth/MaxHealth; };

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
	float MaxHealth = 100.0f;

	float CurrentHealth = 100.0f;

	virtual void BeginPlay() override;
};
