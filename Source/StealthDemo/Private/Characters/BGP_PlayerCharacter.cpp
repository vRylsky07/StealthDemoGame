#include "Characters/BGP_PlayerCharacter.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "BGP_Utils.h"
#include "Components/SD_HealthComponent.h"

ABGP_PlayerCharacter::ABGP_PlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

}

void ABGP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ABGP_PlayerCharacter::OverlapOn);
	OnActorEndOverlap.AddDynamic(this, &ABGP_PlayerCharacter::OverlapOff);

	
}

void ABGP_PlayerCharacter::OverlapOn(AActor* OwnerActor, AActor* OtherActor)
{
	if(!OtherActor->Tags.Contains(FName("Interactive"))) return;

	for (int32 i = 0; i < InteractiveActors.Num(); ++i)
	{
		BGP_Utils::SetCustomDepthForAll(false, InteractiveActors[i]);
		BGP_Utils::SetActorWidgetHidden(true, InteractiveActors[i]);
	};

	BGP_Utils::SetCustomDepthForAll(true, OtherActor);
	BGP_Utils::SetActorWidgetHidden(false, OtherActor);

	if (!InteractiveActors.Contains(OtherActor)) 
	{
		InteractiveActors.Add(OtherActor);
	};
};

void ABGP_PlayerCharacter::OverlapOff(AActor* OwnerActor, AActor* OtherActor) 
{
	if (!OtherActor->Tags.Contains(FName("Interactive"))) return;

	BGP_Utils::SetCustomDepthForAll(false, OtherActor);
	BGP_Utils::SetActorWidgetHidden(true, OtherActor);

	InteractiveActors.Remove(OtherActor);

	if (InteractiveActors.Num()) {

		BGP_Utils::SetCustomDepthForAll(true, InteractiveActors.Last());
		BGP_Utils::SetActorWidgetHidden(false, InteractiveActors.Last());
	};
	
};

void ABGP_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABGP_PlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bGodmode) return 0.0f;

	const auto HealthComponent = GetComponentByClass(USD_HealthComponent::StaticClass());
	if (!HealthComponent) return 0.0f;

	const auto CastedHealthComp = Cast<USD_HealthComponent>(HealthComponent);
	if (!CastedHealthComp) return 0.0f;

	float CurrentHealth = CastedHealthComp->SetHealth(-Damage);
	if (!CurrentHealth) { OnDeathEvent(); };

	return Damage;
}

void ABGP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

