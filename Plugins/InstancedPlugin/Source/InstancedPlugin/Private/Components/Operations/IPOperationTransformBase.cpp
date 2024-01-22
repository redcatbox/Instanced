// redbox, 2022

#include "Components/Operations/IPOperationTransformBase.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPOperationTransformBase::UIPOperationTransformBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCond = false;
#endif
}

#if WITH_EDITOR
void UIPOperationTransformBase::CopyTransforms()
{
	if (UInstancedStaticMeshComponent* ParentISM = GetParentISMComponent())
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
