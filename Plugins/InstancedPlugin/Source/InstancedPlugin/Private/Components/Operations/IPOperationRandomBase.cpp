// redbox, 2020

#include "Components/Operations/IPOperationRandomBase.h"

UIPOperationRandomBase::UIPOperationRandomBase()
{
#if WITH_EDITORONLY_DATA
	bUseRandomStream = false;
	RandomStreamSeed = 0;
	RandomStream.Initialize(RandomStreamSeed);
#endif
}

#if WITH_EDITOR
void UIPOperationRandomBase::RunOperation(TArray<FTransform>& Transforms)
{
	RandomStream.Initialize(RandomStreamSeed);
}
#endif
