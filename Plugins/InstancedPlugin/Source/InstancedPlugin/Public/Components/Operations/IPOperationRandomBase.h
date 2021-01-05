// redbox, 2021

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationRandomBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPOperationRandomBase : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationRandomBase();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bUseRandomStream"))
		int32 RandomStreamSeed;

	UPROPERTY()
		FRandomStream RandomStream;
#endif
};
