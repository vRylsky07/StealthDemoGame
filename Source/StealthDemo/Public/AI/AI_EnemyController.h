// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI_EnemyController.generated.h"

UCLASS()
class STEALTHDEMO_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AActor* GetEnemy();

	FVector FindNoiseTriggers();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HeightToEnemy = 350;
};
