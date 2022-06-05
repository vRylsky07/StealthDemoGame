// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_EnemyController.h"
#include "Components/BGT_PlayerStatsAbilitiesComp.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/BGP_HidingObjectsStateComp.h"
#include "Perception/AISense_Hearing.h"

AActor* AAI_EnemyController::GetEnemy()
{
	const auto PerceptionComponent1 = FindComponentByClass<UAIPerceptionComponent>();
	if (!PerceptionComponent1) return nullptr;

	TArray<AActor*> FoundActors;

	PerceptionComponent1->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0) 
	{
		return nullptr;
	};

	APawn* EnemyPawn = nullptr;

	for (auto Actor : FoundActors) 
	{
		const auto Pawn1 = Cast<APawn>(Actor);

		if (Pawn1->IsPlayerControlled()) 
		{
			const auto EnemyUsingObjBoolComp = Pawn1->FindComponentByClass<UBGT_PlayerStatsAbilitiesComp>();
			if (!EnemyUsingObjBoolComp) continue;

			if (EnemyUsingObjBoolComp->GetHidingInSomeObject()) continue;

			EnemyPawn = Pawn1;
			break;
		};



		const auto HidingObjStateComp = Pawn1->FindComponentByClass<UBGP_HidingObjectsStateComp>();
		if (!HidingObjStateComp) continue;
		
		if (HidingObjStateComp->GetPlayerUsingAnimationOn()) 
		{
			EnemyPawn = Pawn1;
			break;
		};
	};

	if (!EnemyPawn) return nullptr;

	const auto EnemyStatsComponent = EnemyPawn->FindComponentByClass<UBGT_PlayerStatsAbilitiesComp>();
	if (!EnemyStatsComponent) return nullptr;

	const auto SightSense = PerceptionComponent1->GetSenseConfig(UAISense_Sight::GetSenseID(UAISense_Sight::StaticClass()));
	if (!SightSense) return nullptr;

	const auto ConfigSight = Cast<UAISenseConfig_Sight>(SightSense);
	if (!ConfigSight) return nullptr;

	float FinalSightRadius = ConfigSight->SightRadius - EnemyStatsComponent->GetFinalInvisibleScore();
	float CurrentDistanceToEnemy = (EnemyPawn->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
	float HeightDistance = (EnemyPawn->GetActorLocation().Z - GetPawn()->GetActorLocation().Z);

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Distance to find: %f"), FinalSightRadius));

	if ((CurrentDistanceToEnemy >= FinalSightRadius) || (HeightDistance > HeightToEnemy)) { return nullptr; };

	if (!EnemyPawn->IsPlayerControlled())
	{
		const auto HidingObjStateComp = EnemyPawn->FindComponentByClass<UBGP_HidingObjectsStateComp>();
		if (!HidingObjStateComp) return nullptr;
		HidingObjStateComp->ClearUsingDelayTimer();
	};


	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Current distance to Enemy: %f"), CurrentDistanceToEnemy));

	return EnemyPawn;
};

FVector AAI_EnemyController::FindNoiseTriggers()
{
	const auto PerceptionComponent1 = FindComponentByClass<UAIPerceptionComponent>();
	if (!PerceptionComponent1) return FVector::ZeroVector;

	TArray<AActor*> FoundActors;

	PerceptionComponent1->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0) { return FVector::ZeroVector; };


	float ClosestNoiseDistance = MAX_FLT;
	AActor* ClosestNoiseTrigger = nullptr;

	for (auto Actor : FoundActors) 
	{
		float DistanceToActor = (Actor->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
		float HeightDistance = Actor->GetActorLocation().Z - GetPawn()->GetActorLocation().Z;
		if ((DistanceToActor < ClosestNoiseDistance) && (HeightDistance < HeightToEnemy))
		{
			ClosestNoiseTrigger = Actor;
		};
	};

	if (!ClosestNoiseTrigger) return FVector::ZeroVector;

	return ClosestNoiseTrigger->GetActorLocation();
;
}

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTreeAsset);
}
