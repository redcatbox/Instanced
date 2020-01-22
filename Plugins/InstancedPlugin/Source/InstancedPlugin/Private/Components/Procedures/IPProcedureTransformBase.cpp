// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformBase.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPProcedureTransformBase::UIPProcedureTransformBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformBase::CopyTransforms()
{
	UInstancedStaticMeshComponent* ParentISM = GetParentISMComponent();
	
	if (ParentISM)
	{
		OperationTransforms.Empty();

		for (int32 i = 0; i < ParentISM->GetInstanceCount(); i++)
		{
			FTransform Transf = FTransform();
			ParentISM->GetInstanceTransform(i, Transf, false);
			OperationTransforms.Add(FPerInstanceTransform(i, Transf));
		}
	}
}
#endif