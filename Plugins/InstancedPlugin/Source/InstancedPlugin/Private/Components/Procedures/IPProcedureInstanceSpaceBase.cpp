// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureInstanceSpaceBase.h"

UIPProcedureInstanceSpaceBase::UIPProcedureInstanceSpaceBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bInstanceSpaceEditCond = true;
	InstanceSpace = FVector(100.f);
	InstanceSpaceInternal = InstanceSpace;
	bInstanceSpaceFromMeshBounds = false;
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
			InstanceSpaceInternal = ParentISMComp->GetStaticMesh()->GetBounds().GetBox().GetSize();
		}
	}
	else
	{
		InstanceSpaceInternal = InstanceSpace;
	}
}
#endif