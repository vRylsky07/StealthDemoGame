// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BGT_PlayerStatsAbilitiesComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHDEMO_API UBGT_PlayerStatsAbilitiesComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBGT_PlayerStatsAbilitiesComp();

	float GetFinalInvisibleScore(){return FinalInvisibleScore;};

	UFUNCTION(BlueprintCallable)
	float GetFinalInvisibleScoreBP() { return FinalInvisibleScore; };

	UFUNCTION(BlueprintCallable)
	float GetFinalInvisiblePercentBP() { return FinalInvisibleScore / DefaultFinalInvisibleScore; };

	UFUNCTION(BlueprintCallable)
	void SetHidingInSomeObject(bool bHide) { HidingInSomeObject = bHide; };

	UFUNCTION(BlueprintCallable)
	bool GetHidingInSomeObject() const { return HidingInSomeObject; };

	UFUNCTION(BlueprintCallable)
	void SetFinalInvisibleScore(float NewFinalInvisibleScore) 
	{
		FinalInvisibleScore = NewFinalInvisibleScore;
		return;
	};

	UFUNCTION(BlueprintCallable)
	void ResetFinalInvisibleScore()
	{
		FinalInvisibleScore = DefaultFinalInvisibleScore;
		return;
	};

	UFUNCTION(BlueprintCallable)
	float GetDefaultInvisibleScore() const
	{
		return DefaultFinalInvisibleScore;
	};

	UFUNCTION(BlueprintCallable)
		float GetCrawlInvisibleMultiply() const
	{
		return CrawlInvisibleMultiply;
	};

	UFUNCTION(BlueprintCallable)
		void SetCrawlInvisibleMultiply(float NewValue)
	{
		CrawlInvisibleMultiply = NewValue;
		FinalInvisibleScore = InvisibleScore * CrawlInvisibleMultiply;
		DefaultFinalInvisibleScore = FinalInvisibleScore;
		return;
	};

	UFUNCTION(BlueprintCallable)
	AActor* GetClosestLightPoint();


	float  GetDistanceToEnemy(AActor* LightPoint);
	bool CanTrace(AActor* LightPoint);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	// Invisible Score reducing enemy`s sight radius to notice player (0 means full Sight Radius range)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
	float InvisibleScore = 2300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool IsNotPlayer = false;

	UPROPERTY()
	float CrawlInvisibleMultiply = 1.0f;

	float DefaultFinalInvisibleScore;
	float FinalInvisibleScore = InvisibleScore * CrawlInvisibleMultiply;

	bool HidingInSomeObject = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool DebugBool = false;

	virtual void BeginPlay() override;
};
