// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureInstanceSpaceBase.h"

UIPProcedureInstanceSpaceBase::UIPProcedureInstanceSpaceBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bInstanceSpaceEditCond = true;
	InstanceSpace = FVector(100.f);
	bInstanceSpaceFromMeshBounds = false;
	bInstanceSpaceFromMeshBoundsWithCurrentScale = true;
	bHalfSpaceOffset = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureInstanceSpaceBase::RunProcedure(TArray<FTransform>& Transforms)
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