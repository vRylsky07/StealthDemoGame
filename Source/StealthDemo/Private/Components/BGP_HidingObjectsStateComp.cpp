// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BGP_HidingObjectsStateComp.h"

UBGP_HidingObjectsStateComp::UBGP_HidingObjectsStateComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBGP_HidingObjectsStateComp::SetUsingDelayTimer(float UsingTime)
{
	if (!GetWorld()) return;

	const auto OwnerHidingStateComp = GetOwnerHidingStateComp();
		
	OwnerHidingStateComp->SetPlayerUsingAnimationOn(true);

	auto UsingAnimationOff = [OwnerHidingStateComp]() {OwnerHidingStateComp->SetPlayerUsingAnimationOn(false); };

	GetWorld()->GetTimerManager().SetTimer(UsingDelayTimer, UsingAnimationOff, UsingTime, false, -1.0f);
}

void UBGP_HidingObjectsStateComp::ClearUsingDelayTimer()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(UsingDelayTimer);
	
	//const auto OwnerHidingStateComp = GetOwnerHidingStateComp();
	//OwnerHidingStateComp->SetPlayerUsingAnimationOn(false);
}

UBGP_HidingObjectsStateComp * UBGP_HidingObjectsStateComp::GetOwnerHidingStateComp()
{
	const auto HidingObjectsStateBaseComp = GetOwner()->GetComponentByClass(UBGP_HidingObjectsStateComp::StaticClass());
	if (!HidingObjectsStateBaseComp) return nullptr;

	const auto HidingObjectsStateComp = Cast<UBGP_HidingObjectsStateComp>(HidingObjectsStateBaseComp);
	if (!HidingObjectsStateComp) return nullptr;

	return HidingObjectsStateComp;
};

void UBGP_HidingObjectsStateComp::BeginPlay()
{
	Super::BeginPlay();

}


