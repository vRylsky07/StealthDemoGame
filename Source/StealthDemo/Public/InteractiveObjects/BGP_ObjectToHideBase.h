// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BGP_ObjectToHideBase.generated.h"

UCLASS()
class STEALTHDEMO_API ABGP_ObjectToHideBase : public APawn
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	USoundBase* GetHittedSound() const { return HittedSound; };

	UFUNCTION(BlueprintCallable)
	USoundBase* GetExplodeSound() const { return ExplodeSound; };

	UFUNCTION(BlueprintCallable)
	AActor* GetDestructibleToSpawn() const { return DestructibleActor; };

public:
	ABGP_ObjectToHideBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HittedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* ExplodeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AActor> DestructibleToSpawn;

	AActor * DestructibleActor;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
