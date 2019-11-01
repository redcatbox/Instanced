// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
//#include "CollisionQueryParams.h"
#include "Kismet/KismetSystemLibrary.h"
#include "IPProcedureAlignBase.generated.h"

UCLASS(Abstract, NotBlueprintable, ClassGroup = (Procedure), AutoExpandCategories = ("Procedure | TraceParameters"))
class INSTANCEDPLUGIN_API UIPProcedureAlignBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureAlignBase();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should orient to surface? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bAlignToSurface;

	/** Should reverse alignment? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bReverse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		bool bTraceComplex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		bool bIgnoreSelf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | TraceParameters")
		float DrawTime;
#endif
};