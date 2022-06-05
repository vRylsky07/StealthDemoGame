// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Lights/BGP_BaseLightActor.h"
#include "Components/SphereComponent.h"

ABGP_BaseLightActor::ABGP_BaseLightActor()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
	CollisionComponent->InitSphereRadius(DistanceToAffect.Y);
	SetRootComponent(CollisionComponent);
	PrimaryActorTick.bCanEverTick = false;
}

void ABGP_BaseLightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

float ABGP_BaseLightActor::CalculateFinalInvisibleScore(float CurrentDistance, float DefaultFinalInvisibleScore)
{
	const auto FinalInvisibleScore = FMath::GetMappedRangeValueClamped(
		DistanceToAffect, 
		FVector2D((1.0f - InvisibleAffectMax) * DefaultFinalInvisibleScore, DefaultFinalInvisibleScore), 
		CurrentDistance
	);

	return FinalInvisibleScore;
};


