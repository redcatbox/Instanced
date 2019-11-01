// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformBase.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPProcedureTransformBase::UIPProcedureTransformBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bApplyToLocation = true;
	bApplyToRotation = true;
	bApplyToScale = true;
#endif
}

FTransform UIPProcedureTransformBase::Operation(FTransform& A, FTransform& B)
{
	return FTransform();
}