// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "BGP_HidingObjectsStateComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHDEMO_API UBGP_HidingObjectsStateComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBGP_HidingObjectsStateComp();

	UFUNCTION(BlueprintCallable)
	bool GetPlayerUsingAnimationOn() const { return PlayerUsingAnimationOn; };

	UFUNCTION(BlueprintCallable)
	void SetPlayerUsingAnimationOn(bool bUse) { PlayerUsingAnimationOn = bUse; };

	UFUNCTION(BlueprintCallable)
	void SetUsingDelayTimer(float UsingTime);

	UFUNCTION(BlueprintCallable)
	void ClearUsingDelayTimer();

	UBGP_HidingObjectsStateComp * GetOwnerHidingStateComp();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	bool PlayerUsingAnimationOn = false;

	UPROPERTY()
	FTimerHandle UsingDelayTimer;

	virtual void BeginPlay() override;
};
