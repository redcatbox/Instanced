// redbox, 2020

#pragma once

#include "IPOperationAlignBase.h"
#include "IPOperationAlignByDirection.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationAlignByDirection : public UIPOperationAlignBase
{
	GENERATED_BODY()

public:
	UIPOperationAlignByDirection();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Direction to align */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignDirection;
#endif
};
