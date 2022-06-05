// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BGP_PlayerCharacter.generated.h"

UCLASS()
class STEALTHDEMO_API ABGP_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABGP_PlayerCharacter();

protected:
	AActor* LastOverlappedActor;
	TArray<AActor*> InteractiveActors;

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cheats")
	bool bGodmode = false;

	UFUNCTION()
	void OverlapOn(AActor * OwnerActor, AActor * OtherActor);

	UFUNCTION()
	void OverlapOff(AActor* OwnerActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetInteractiveActors() const { return InteractiveActors; };

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void OnDeathEvent();

	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
