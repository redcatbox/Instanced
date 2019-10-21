// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureDynamicTransform.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Actors/IPBaseInstancedActor.h"

UIPProcedureDynamicTransform::UIPProcedureDynamicTransform()
{
	PrimaryComponentTick.bCanEverTick = true;

	DynamicTransformDelta = FTransform();
	DynamicDistance = 1000.f;
	DynamicNearFactor = 0.1f;
	DynamicFarFactor = 0.1f;
}

void UIPProcedureDynamicTransform::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	DynamicNearFactor = FMath::Clamp(DynamicNearFactor, 0.f, 1.f - DynamicFarFactor);
	DynamicFarFactor = FMath::Clamp(DynamicFarFactor, 0.f, 1.f - DynamicNearFactor);

	if (AIPBaseInstancedActor* BaseInstancedActor = Cast<AIPBaseInstancedActor>(GetOwner()))
	{
		FTransform InstanceTransformOld;
		FTransform InstanceTransformNew;
		InstancesTransformsOld.Empty();
		InstancesTransformsNew.Empty();

		for (int32 i = 0; i < BaseInstancedActor->InstancesNum; i++)
		{
			BaseInstancedActor->ISMComponent->GetInstanceTransform(i, InstanceTransformOld, true);
			InstancesTransformsOld.Add(InstanceTransformOld);

			InstanceTransformNew.SetLocation(InstanceTransformOld.GetLocation() + DynamicTransformDelta.GetLocation());
			InstanceTransformNew.SetRotation(InstanceTransformOld.GetRotation() * DynamicTransformDelta.GetRotation());
			InstanceTransformNew.SetScale3D(InstanceTransformOld.GetScale3D() + DynamicTransformDelta.GetScale3D());
			InstancesTransformsNew.Add(InstanceTransformNew);
		}
	}
}

void UIPProcedureDynamicTransform::RunProcedureDynamic()
{
	FVector CameraLocation = FVector::ZeroVector;

	if (GEngine)
		CameraLocation = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->GetCameraLocation();

	float Distance = DynamicDistance + 1.f;
	int32 LastModifiedInstanceIndex = -1;
	bool bInstanceModified = false;
	float LerpAlpha = 0;

	if (AIPBaseInstancedActor* BaseInstancedActor = Cast<AIPBaseInstancedActor>(GetOwner()))
	{
		FTransform InstanceTransformNew;

		for (int32 i = 0; i < BaseInstancedActor->InstancesNum; i++)
		{
			Distance = (CameraLocation - InstancesTransformsOld[i].GetLocation()).Size();

			if (Distance <= DynamicDistance)
			{
				LastModifiedInstanceIndex = i;
				bInstanceModified = true;
				LerpAlpha = 1 - (Distance / DynamicDistance - DynamicNearFactor) / (1.f - DynamicNearFactor - DynamicFarFactor);
				LerpAlpha = FMath::Clamp(LerpAlpha, 0.f, 1.f);

				InstanceTransformNew.SetLocation(FMath::Lerp(InstancesTransformsOld[i].GetLocation(), InstancesTransformsNew[i].GetLocation(), LerpAlpha));
				InstanceTransformNew.SetRotation(FMath::Lerp(InstancesTransformsOld[i].GetRotation(), InstancesTransformsNew[i].GetRotation(), LerpAlpha));
				InstanceTransformNew.SetScale3D(FMath::Lerp(InstancesTransformsOld[i].GetScale3D(), InstancesTransformsNew[i].GetScale3D(), LerpAlpha));

				BaseInstancedActor->ISMComponent->UpdateInstanceTransform(i, InstanceTransformNew, true, false, false);
			}
		}

		if (bInstanceModified)
			BaseInstancedActor->ISMComponent->MarkRenderStateDirty();
	}
}