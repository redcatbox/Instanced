// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationRandomBase.h"
#include "IPOperationTransformsContribution.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformsContribution : public UIPOperationRandomBase
{
	GENERATED_BODY()

public:
	UIPOperationTransformsContribution();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float ContributionRangeStart;

	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float ContributionRangeEnd;
#endif
};