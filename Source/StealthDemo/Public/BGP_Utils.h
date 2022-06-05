#pragma once

#include "Components/WidgetComponent.h"

class BGP_Utils
{
public:
	template<typename T>
	void static SetCustomDepthToMesh(bool bDepth, AActor* OverlappedActor)
	{
		TArray<T*> MeshComponents;
		OverlappedActor->GetComponents<T>(MeshComponents);



		for (auto Component : MeshComponents)
		{
			Component->SetRenderCustomDepth(bDepth);
		};
		return;
	};

	void static SetCustomDepthForAll(bool bDepth, AActor * Actor)
	{
		SetCustomDepthToMesh<UStaticMeshComponent>(bDepth, Actor);
		SetCustomDepthToMesh<USkeletalMeshComponent>(bDepth, Actor);
	}

	void static SetActorWidgetHidden(bool bDepth, AActor* OverlappedActor)
	{
		TArray<UWidgetComponent*> WidgetComponents;
		OverlappedActor->GetComponents<UWidgetComponent>(WidgetComponents);

		for (auto Component : WidgetComponents)
		{
			Component->SetHiddenInGame(bDepth);
		};
		
		return;
	};

};