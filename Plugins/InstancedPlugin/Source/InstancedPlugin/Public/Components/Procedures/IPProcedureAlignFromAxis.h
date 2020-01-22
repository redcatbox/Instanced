// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureAlignBase.h"
#include "IPProcedureAlignFromAxis.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAlignFromAxis : public UIPProcedureAlignBase
{
	GENERATED_BODY()

public:
	UIPProcedureAlignFromAxis();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Axis start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisStart;

	/** Axis end */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisEnd;

	/** Distance to align at */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ClampMin = "0", UIMin = "0"))
		float AlignDistance;
#endif
};