// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomBase.h"

UIPProcedureRandomBase::UIPProcedureRandomBase()
{
#if WITH_EDITORONLY_DATA
	bUseRandomStream = false;
	RandomStreamSeed = 0;
	RandomStream.Initialize(RandomStreamSeed);
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomBase::RunProcedure(TArray<FTransform>& Transforms)
{
	RandomStream.Initialize(RandomStreamSeed);
}
#endif