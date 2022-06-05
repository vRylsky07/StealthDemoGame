// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/BGP_ObjectToHideBase.h"
#include "Components/BGP_HidingObjectsStateComp.h"

ABGP_ObjectToHideBase::ABGP_ObjectToHideBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABGP_ObjectToHideBase::BeginPlay()
{
	Super::BeginPlay();
	DestructibleActor = Cast<AActor>(DestructibleToSpawn);
}

void ABGP_ObjectToHideBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABGP_ObjectToHideBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

