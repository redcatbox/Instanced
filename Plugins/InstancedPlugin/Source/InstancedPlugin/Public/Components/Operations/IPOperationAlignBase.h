// redbox, 2021

#pragma once

#include "IPOperationComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "IPOperationAlignBase.generated.h"

UCLASS(Abstract, AutoExpandCategories = ("Operation | TraceParameters"))
class INSTANCEDPLUGIN_API UIPOperationAlignBase : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationAlignBase();

#if WITH_EDITORONLY_DATA
	/** Should orient to surface? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bAlignToSurface;

	/** How much to offset location in trace direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		float OffsetInTraceDirection;

	/** Should reverse alignment? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bReverse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		bool bTraceComplex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		bool bIgnoreSelf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | TraceParameters")
		float DrawTime;
#endif
};
