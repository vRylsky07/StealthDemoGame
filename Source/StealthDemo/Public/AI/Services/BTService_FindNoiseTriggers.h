// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindNoiseTriggers.generated.h"

UCLASS()
class STEALTHDEMO_API UBTService_FindNoiseTriggers : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FindNoiseTriggers();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector NoiseTarget;
};
