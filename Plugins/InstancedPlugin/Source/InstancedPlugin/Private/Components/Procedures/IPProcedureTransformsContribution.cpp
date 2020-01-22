// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformsContribution.h"

UIPProcedureTransformsContribution::UIPProcedureTransformsContribution()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	ContributionRangeStart = 0.f;
	ContributionRangeEnd = 1.f;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformsContribution::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);
	ContributionRangeEnd = FMath::Clamp(ContributionRangeEnd, ContributionRangeStart, ContributionRangeEnd);
	TArray<FTransform> ResultTransforms;

	if (Transforms.Num() <= 1)
	{
		return;
	}

	if (bUseRandomStream)
	{
		UIPFunctionLibrary::ShuffleArray(Transforms, bUseRandomStream, RandomStream);
	}

	int32 IdStart = (float)(Transforms.Num() - 1) * ContributionRangeStart;
	int32 IdEnd = IdStart + (float)(Transforms.Num() - 1) * FMath::Abs(ContributionRangeEnd - ContributionRangeStart);

	for (int i = IdStart; i <= IdEnd; i++)
	{
		ResultTransforms.Add(Transforms[i]);
	}

	Transforms = ResultTransforms;
}
#endif