// redbox, 2021

#include "Actors/IPSplineMeshGradientActor.h"
#include "Materials/MaterialInstanceDynamic.h"

AIPSplineMeshGradientActor::AIPSplineMeshGradientActor()
{
	GradientStartMaterialParameter = FName(TEXT("GradientStart"));
	GradientEndMaterialParameter = FName(TEXT("GradientEnd"));

#if WITH_EDITORONLY_DATA
	bInverseGradient = false;
#endif
}

#if WITH_EDITOR
void AIPSplineMeshGradientActor::RunGeneration()
{
	Super::RunGeneration();
	GenerateSplineGradient();
}

void AIPSplineMeshGradientActor::GenerateSplineGradient()
{
	int32 SplinePointsNumber = SplineComponent->GetNumberOfSplinePoints();
	const bool bLoop = SplineComponent->IsClosedLoop();

	if (SplinePointsNumber > 1)
	{
		if (!bLoop)
		{
			SplinePointsNumber = SplinePointsNumber - 1;
		}

		if (SplineMeshComponent->GetStaticMesh())
		{
			for (int32 i = 0; i < SplinePointsNumber; i++)
			{
				const int32 IndexCurrent = i;
				const int32 IndexNext = IndexCurrent + 1;
				const float SplineLength = SplineComponent->GetSplineLength();

				for (int32 j = 0; j < SplineMeshComponents[IndexCurrent]->GetNumMaterials(); j++)
				{
					if (UMaterialInterface* Material = SplineMeshComponents[IndexCurrent]->GetMaterial(j))
					{
						UMaterialInstanceDynamic* MID = SplineMeshComponents[IndexCurrent]->CreateDynamicMaterialInstance(j, Material);
						const float GradientStart = bInverseGradient ?
							SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexCurrent) / SplineLength : 1.f - SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexCurrent) / SplineLength;
						const float GradientEnd = bInverseGradient ?
							SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexNext) / SplineLength : 1.f - SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexNext) / SplineLength;
						MID->SetScalarParameterValue(GradientStartMaterialParameter, GradientStart);
						MID->SetScalarParameterValue(GradientEndMaterialParameter, GradientEnd);
					}
				}
			}
		}
	}
}
#endif
