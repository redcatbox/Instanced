// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/Procedures/IPProcedureComponent.h"
#include "IPBaseInstancedActor.generated.h"

USTRUCT()
struct FSortByExecutionOrder
{
	GENERATED_BODY()

	FSortByExecutionOrder() {}

	bool operator()(const UIPProcedureComponent* A, const UIPProcedureComponent* B) const
	{
		int32 ExecutionOrderA = A->ExecutionOrder;
		int32 ExecutionOrderB = B->ExecutionOrder;
		return ExecutionOrderA < ExecutionOrderB;
	}
};

UCLASS(Abstract, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPBaseInstancedActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunGeneration() override;
#endif
};