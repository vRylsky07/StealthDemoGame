// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SD_HealthComponent.h"

USD_HealthComponent::USD_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float USD_HealthComponent::SetHealth(float healthAdd)
{
	if ((CurrentHealth + healthAdd) <= 0) 
	{
		CurrentHealth = 0;
		return 0;
	};

	if ((CurrentHealth + healthAdd) >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
		return CurrentHealth;
	};

	CurrentHealth = CurrentHealth + healthAdd;

	return CurrentHealth;
}

void USD_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}


