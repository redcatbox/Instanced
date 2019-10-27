// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomBase.h"

UIPProcedureRandomBase::UIPProcedureRandomBase()
{
#if WITH_EDITORONLY_DATA
	bUseRandomStreamEditCondition = true;
	bUseRandomStream = false;
	bUseRandomStreamSeedEditCondition = bUseRandomStream && bUseRandomStreamEditCondition;
	RandomStreamSeed = 0;
	RandomStream.Initialize(RandomStreamSeed);
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomBase::RunProcedure(TArray<FTransform>& Transforms)
{
	bUseRandomStreamSeedEditCondition = bUseRandomStream && bUseRandomStreamEditCondition;
	RandomStream.Initialize(RandomStreamSeed);
}
#endif