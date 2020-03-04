// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationInstanceSpaceBase.h"

UIPOperationInstanceSpaceBase::UIPOperationInstanceSpaceBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bInstanceSpaceEditCond = true;
	InstanceSpace = FVector(100.f);
	bInstanceSpaceFromMeshBounds = false;
	bInstanceSpaceFromMeshBoundsWithCurrentScale = true;
	bHalfSpaceOffsetEditCond = false;
	bHalfSpaceOffset = false;
#endif
}

#if WITH_EDITOR
void UIPOperationInstanceSpaceBase::RunOperation(TArray<FTransform>& Transforms)
{
	bInstanceSpaceEditCond = !bInstanceSpaceFromMeshBounds;

	if (bInstanceSpaceFromMeshBounds)
	{
		if (UInstancedStaticMeshComponent* ParentISMComp = GetParentISMComponent())
		{
			UStaticMesh* SM = ParentISMComp->GetStaticMesh();
			if (SM)
			{
				InstanceSpace = SM->GetBounds().GetBox().GetSize();

				if (bInstanceSpaceFromMeshBoundsWithCurrentScale)
				{
					FTransform Transf = FTransform();
					ParentISMComp->GetInstanceTransform(0, Transf);
					InstanceSpace = InstanceSpace * Transf.GetScale3D();
				}
			}
		}
	}
}
#endif