// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGP_BaseLightActor.generated.h"

class USphereComponent;

UCLASS()
class STEALTHDEMO_API ABGP_BaseLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABGP_BaseLightActor();

	bool GetShouldTrace() { return ShouldTrace; };
	float CalculateFinalInvisibleScore(float CurrentDistance, float DefaultFinalInvisibleScore);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FVector2D DistanceToAffect = FVector2D(0.0f, 1500.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool ShouldTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float InvisibleAffectMax = 0.9f;

	virtual void BeginPlay() override;
};
