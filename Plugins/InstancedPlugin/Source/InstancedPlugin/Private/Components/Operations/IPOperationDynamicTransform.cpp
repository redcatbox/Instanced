// redbox, 2020

#include "Components/Operations/IPOperationDynamicTransform.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPOperationDynamicTransform::UIPOperationDynamicTransform()
{
	DynamicTransformDelta = FTransform();
	DynamicDistance = 1000.f;
	DynamicNearFactor = 0.1f;
	DynamicFarFactor = 0.1f;
}

#if WITH_EDITOR
void UIPOperationDynamicTransform::RunOperation(TArray<FTransform>& Transforms)
{
	DynamicNearFactor = FMath::Clamp(DynamicNearFactor, 0.f, 1.f - DynamicFarFactor);
	DynamicFarFactor = FMath::Clamp(DynamicFarFactor, 0.f, 1.f - DynamicNearFactor);
	ParentISMComp = GetParentISMComponent();

	if (ParentISMComp)
	{
		FTransform InstanceTransformOld;
		FTransform InstanceTransformNew;
		InstancesTransformsOld.Empty();
		InstancesTransformsNew.Empty();

		for (int32 i = 0; i < ParentISMComp->GetInstanceCount(); i++)
		{
			ParentISMComp->GetInstanceTransform(i, InstanceTransformOld, true);
			InstancesTransformsOld.Add(InstanceTransformOld);
			InstanceTransformNew.SetLocation(InstanceTransformOld.GetLocation() + DynamicTransformDelta.GetLocation());
			InstanceTransformNew.SetRotation(InstanceTransformOld.GetRotation() * DynamicTransformDelta.GetRotation());
			// TO DO = scale is not updated
			InstanceTransformNew.SetScale3D(InstanceTransformOld.GetScale3D() + DynamicTransformDelta.GetScale3D());
			InstancesTransformsNew.Add(InstanceTransformNew);
		}
	}
}
#endif

void UIPOperationDynamicTransform::BeginPlay()
{
	Super::BeginPlay();
	ParentISMComp = GetParentISMComponent();
}

void UIPOperationDynamicTransform::RunOperationDynamic()
{
	if (ParentISMComp)
	{
		FVector CameraLocation = FVector::ZeroVector;

		if (GEngine)
		{
			CameraLocation = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->GetCameraLocation();
		}

		float Distance = DynamicDistance + 1.f;
		int32 LastModifiedInstanceIndex = -1;
		bool bInstanceModified = false;
		float LerpAlpha = 0;
		FTransform InstanceTransformNew;

		for (int32 i = 0; i < ParentISMComp->GetInstanceCount(); i++)
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

				ParentISMComp->UpdateInstanceTransform(i, InstanceTransformNew, true, false, false);
			}
		}

		if (bInstanceModified)
		{
			ParentISMComp->MarkRenderStateDirty();
		}
	}
}