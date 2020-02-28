// Dmitriy Barannik aka redbox, 2020

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