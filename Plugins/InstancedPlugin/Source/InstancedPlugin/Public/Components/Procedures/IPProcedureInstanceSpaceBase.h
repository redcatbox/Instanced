// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureInstanceSpaceBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPProcedureInstanceSpaceBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureInstanceSpaceBase();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Space of every instance from it's center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bInstanceSpaceEditCond"))
		FVector InstanceSpace;

	/** Should set instance space from mesh bounds? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bInstanceSpaceFromMeshBounds;

	/** Should instance space include current scale? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bInstanceSpaceFromMeshBounds"))
		bool bInstanceSpaceFromMeshBoundsWithCurrentScale;

	/** Should instances be offset on half space from it's center? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bHalfSpaceOffset;
#endif

protected:
	UPROPERTY()
		bool bInstanceSpaceEditCond;
};