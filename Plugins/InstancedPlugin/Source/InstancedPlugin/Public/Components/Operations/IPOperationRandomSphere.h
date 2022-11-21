// redbox, 2022

#pragma once

#include "IPOperationRandomBase.h"
#include "IPOperationRandomSphere.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationRandomSphere : public UIPOperationRandomBase
{
	GENERATED_BODY()

public:
	UIPOperationRandomSphere();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should location be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
	FVector BoxExtent;

	/** Should instances be generated on sphere surface only? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bOnSurfaceOnly;

	/** Should instances be oriented to sphere center? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bOrientToCenter;
#endif
};
