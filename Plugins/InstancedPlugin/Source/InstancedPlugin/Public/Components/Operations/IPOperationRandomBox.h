// redbox, 2020

#pragma once

#include "IPOperationRandomBase.h"
#include "IPOperationRandomBox.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationRandomBox : public UIPOperationRandomBase
{
	GENERATED_BODY()

public:
	UIPOperationRandomBox();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Box extent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector BoxExtent;

	/** Should instances be generated on box surface only? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bOnSurfaceOnly;
#endif
};