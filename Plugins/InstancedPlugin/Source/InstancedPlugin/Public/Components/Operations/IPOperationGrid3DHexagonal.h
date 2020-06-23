// redbox, 2020

#pragma once

#include "IPOperationGrid3DBase.h"
#include "IPOperationGrid3DHexagonal.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationGrid3DHexagonal : public UIPOperationGrid3DBase
{
	GENERATED_BODY()

public:
	UIPOperationGrid3DHexagonal();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should odd and even rows be fliIPed along X axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bFlipOddEven_X;

	/** Should grid be symmetrical along Y axiz? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bSymmetrical_Y;
#endif
};
