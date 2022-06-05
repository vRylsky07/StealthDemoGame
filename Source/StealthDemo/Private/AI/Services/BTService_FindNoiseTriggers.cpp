// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_FindNoiseTriggers.h"
#include "AI/AI_EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindNoiseTriggers::UBTService_FindNoiseTriggers() 
{
	NodeName = "Find Noise Triggers";
};

void UBTService_FindNoiseTriggers::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto BBComponent = OwnerComp.GetBlackboardComponent();
	if (!BBComponent) return;

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	const auto AIController = Cast<AAI_EnemyController>(Controller);
	if (!AIController) return;

	FVector NoiseTrigger = AIController->FindNoiseTriggers();

	if (BBComponent->IsVectorValueSet(NoiseTarget.SelectedKeyName) && (NoiseTrigger == FVector::ZeroVector)) 
	{
		return;
	};


	if (NoiseTrigger == FVector::ZeroVector)
	{
		BBComponent->ClearValue(NoiseTarget.SelectedKeyName);
		return;
	};

	BBComponent->SetValueAsVector(NoiseTarget.SelectedKeyName, NoiseTrigger);

	return;
};