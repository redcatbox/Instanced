// redbox, 2020

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/Operations/IPOperationComponent.h"
#include "IPBaseInstancedActor.generated.h"

USTRUCT()
struct FSortByExecutionOrder
{
	GENERATED_BODY()

	FSortByExecutionOrder() {}

	bool operator()(const UIPOperationComponent* A, const UIPOperationComponent* B) const
	{
		const int32 ExecutionOrderA = A->ExecutionOrder;
		const int32 ExecutionOrderB = B->ExecutionOrder;
		return ExecutionOrderA < ExecutionOrderB;
	}
};

UCLASS(Abstract)
class INSTANCEDPLUGIN_API AIPBaseInstancedActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunGeneration() override;
#endif
};
