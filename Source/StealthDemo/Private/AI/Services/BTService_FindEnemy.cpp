// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_FindEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI_EnemyController.h"
#include "Components/BGT_PlayerStatsAbilitiesComp.h"
#include "Characters/BGP_PlayerCharacter.h"

UBTService_FindEnemy::UBTService_FindEnemy() 
{
	NodeName = "Find Enemy";
};

void UBTService_FindEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto BBComponent = OwnerComp.GetBlackboardComponent();
	if (!BBComponent) return;

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	const auto AIController = Cast<AAI_EnemyController>(Controller);
	if (!AIController) return;

	AActor* EnemyActor = AIController->GetEnemy();
	if (!EnemyActor) 
	{ 
		
	 	if (BBComponent->GetValueAsObject(EnemyKey.SelectedKeyName)) 
		{
			auto const ObjectToCheck = BBComponent->GetValueAsObject(EnemyKey.SelectedKeyName);
			auto const ActorToCheck = Cast<AActor>(ObjectToCheck);
		
			if (!ActorToCheck) return;

			auto const StatsComp = ActorToCheck->GetComponentByClass(UBGT_PlayerStatsAbilitiesComp::StaticClass());
			if (!StatsComp) return;

			auto const StatsCompCasted = Cast<UBGT_PlayerStatsAbilitiesComp>(StatsComp);
			if (!StatsCompCasted) return;

			if (StatsCompCasted->GetHidingInSomeObject()) 
			{
				auto const HidingPlayer = Cast<ABGP_PlayerCharacter>(ActorToCheck);
				if (!HidingPlayer) return;

				if (!HidingPlayer->GetInteractiveActors().Num()) return;
				auto const LastInteractiveObject = HidingPlayer->GetInteractiveActors().Last();
				if (!LastInteractiveObject) return;

				BBComponent->SetValueAsVector(LastEnemyLocation.SelectedKeyName, LastInteractiveObject->GetActorLocation());
				BBComponent->SetValueAsObject(EnemyKey.SelectedKeyName, LastInteractiveObject);
				AIController->SetFocus(LastInteractiveObject);

				return;
			};
		};

		BBComponent->ClearValue(EnemyKey.SelectedKeyName);

		AIController->SetFocus(nullptr);
		return;
	}

	BBComponent->SetValueAsVector(LastEnemyLocation.SelectedKeyName, EnemyActor->GetActorLocation());
	BBComponent->SetValueAsObject(EnemyKey.SelectedKeyName, EnemyActor);

	AIController->SetFocus(EnemyActor);

	return;
};