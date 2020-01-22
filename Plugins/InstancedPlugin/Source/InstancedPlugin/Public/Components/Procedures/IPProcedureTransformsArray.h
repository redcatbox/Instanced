
// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureTransformsArray.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformsArray : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureTransformsArray();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Array of transforms for instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		TArray<FTransform> PlacementTransforms;
#endif
};