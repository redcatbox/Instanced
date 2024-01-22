// redbox, 2022

#include "Components/Operations/IPOperationInstanceSpaceBase.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPOperationInstanceSpaceBase::UIPOperationInstanceSpaceBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCond = false;
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
			if (UStaticMesh* SM = ParentISMComp->GetStaticMesh())
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
