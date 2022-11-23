// redbox, 2022

#include "Components/Operations/IPOperationTransformContribution.h"
#include "Objects/IPFunctionLibrary.h"

UIPOperationTransformContribution::UIPOperationTransformContribution()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	ContributionRangeStart = 0.f;
	ContributionRangeEnd = 1.f;
#endif
}

#if WITH_EDITOR
void UIPOperationTransformContribution::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);

	if (Transforms.Num() <= 1)
	{
		return;
	}

	ContributionRangeEnd = FMath::Clamp(ContributionRangeEnd, ContributionRangeStart, ContributionRangeEnd);

	if (bUseRandomStream)
	{
		UIPFunctionLibrary::ShuffleArray(Transforms, bUseRandomStream, RandomStream);
	}

	int32 IdStart = static_cast<float>(Transforms.Num()) * ContributionRangeStart;
	IdStart = FMath::Clamp(IdStart, 0, Transforms.Num() - 1);
	int32 IdEnd = IdStart + static_cast<float>(Transforms.Num()) * (ContributionRangeEnd - ContributionRangeStart);
	IdEnd = FMath::Clamp(IdEnd, IdStart, Transforms.Num() - 1);

	TArray<FTransform> ResultTransforms;

	for (int i = IdStart; i <= IdEnd; i++)
	{
		ResultTransforms.Add(Transforms[i]);
	}

	Transforms = ResultTransforms;
}
#endif
