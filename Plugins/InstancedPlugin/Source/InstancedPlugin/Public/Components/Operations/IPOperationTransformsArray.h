// redbox, 2022

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationTransformsArray.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformsArray : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationTransformsArray();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Array of transforms for instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
	TArray<FTransform> PlacementTransforms;
#endif
};
