// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureRandomBase.h"
#include "IPProcedureRandomBox.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRandomBox : public UIPProcedureRandomBase
{
	GENERATED_BODY()

public:
	UIPProcedureRandomBox();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Box extent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector BoxExtent;

	/** Should instances be generated on box surface only? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOnSurfaceOnly;
#endif
};