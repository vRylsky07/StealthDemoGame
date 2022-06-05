// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BGT_PlayerStatsAbilitiesComp.h"
#include "Objects/Lights/BGP_BaseLightActor.h"

UBGT_PlayerStatsAbilitiesComp::UBGT_PlayerStatsAbilitiesComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}


void UBGT_PlayerStatsAbilitiesComp::BeginPlay()
{
	Super::BeginPlay();
	//RegisterComponentTickFunctions(true);
	FinalInvisibleScore = InvisibleScore * CrawlInvisibleMultiply;
	DefaultFinalInvisibleScore = FinalInvisibleScore;
}

void UBGT_PlayerStatsAbilitiesComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsNotPlayer) return;

	//GEngine->AddOnScreenDebugMessage(-1, 0.02f, FColor::Yellow, FString::Printf(TEXT("%f"), FinalInvisibleScore));

	AActor* LightPoint = GetClosestLightPoint();
	
	if (!LightPoint) 
	{ 
		ResetFinalInvisibleScore();
		return; 
	};

	const auto LightPointToUse = Cast<ABGP_BaseLightActor>(LightPoint);
	if (!LightPointToUse || !GetOwner()) return;

	if (HidingInSomeObject)
	{
		SetFinalInvisibleScore(MAX_FLT);
		return;
	};

	SetFinalInvisibleScore(LightPointToUse->CalculateFinalInvisibleScore(GetDistanceToEnemy(LightPointToUse), GetDefaultInvisibleScore()));
}

bool UBGT_PlayerStatsAbilitiesComp::CanTrace(AActor* LightPoint)
{
	FHitResult HitRes;

	const auto CastedLightPoint = Cast<ABGP_BaseLightActor>(LightPoint);
	if (CastedLightPoint && !CastedLightPoint->GetShouldTrace()) {return true;};

	GetWorld()->LineTraceSingleByChannel(HitRes, 
		LightPoint->GetActorLocation(), 
		GetOwner()->GetActorLocation(), 
		ECollisionChannel::ECC_Visibility, 
		{}, 
		{}
	);



	return !HitRes.bBlockingHit;
};

float UBGT_PlayerStatsAbilitiesComp::GetDistanceToEnemy(AActor* LightPoint) 
{
	FVector LightLocation = LightPoint->GetActorLocation();
	LightLocation.Z = 0;
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	OwnerLocation.Z = 0;
	float DistanceToLight = (LightLocation - OwnerLocation).Size();
	return DistanceToLight;
};

AActor* UBGT_PlayerStatsAbilitiesComp::GetClosestLightPoint() 
{
	TArray<AActor*> OverlappedLights;
	const auto Owner = GetOwner();
	if (!Owner) return nullptr;

	Owner->GetOverlappingActors(OverlappedLights, ABGP_BaseLightActor::StaticClass());
	if (!OverlappedLights.Num()) return nullptr;

	AActor* ClosestActor = nullptr;
	float ShortestDistance = MAX_FLT;

	for (auto Light : OverlappedLights) 
	{
		FVector LightLocation = Light->GetActorLocation();
		LightLocation.Z = 0;
		FVector OwnerLocation = Owner->GetActorLocation();
		OwnerLocation.Z = 0;

		float DistanceToLight = (LightLocation - OwnerLocation).Size();
		
		if (CanTrace(Light) && DistanceToLight < ShortestDistance)
		{
			ClosestActor = Light;
			ShortestDistance = DistanceToLight;
		};
	};

	if (!ClosestActor) return nullptr;

	return ClosestActor;
};
