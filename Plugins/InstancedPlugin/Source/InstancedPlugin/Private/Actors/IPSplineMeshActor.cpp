// redbox, 2020

#include "Actors/IPSplineMeshActor.h"
#include "Kismet/KismetSystemLibrary.h"

AIPSplineMeshActor::AIPSplineMeshActor()
{
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMeshComponent"));
	SplineMeshComponent->SetupAttachment(RootComponent);
	SplineMeshComponent->Mobility = EComponentMobility::Static;
	SplineMeshComponents.Add(SplineMeshComponent);

#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;
	SplineComponent->bIsEditorOnly = true;
#endif
}

void AIPSplineMeshActor::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	SplineComponent->bSplineHasBeenEdited = true;
	RunGeneration();
#endif
}

#if WITH_EDITOR
void AIPSplineMeshActor::RunGeneration()
{
	if (SplineMeshComponents.Num() > 0)
	{
		for (int32 i = 1; i < SplineMeshComponents.Num(); i++)
		{
			if (SplineMeshComponents[i])
			{
				SplineMeshComponents[i]->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				SplineMeshComponents[i]->UnregisterComponent();
				SplineMeshComponents[i]->DestroyComponent();
			}

			SplineMeshComponents.RemoveAt(i);
		}
	}

	int32 SplinePointsNumber = SplineComponent->GetNumberOfSplinePoints();
	const bool bLoop = SplineComponent->IsClosedLoop();

	if (SplinePointsNumber > 1)
	{
		if (!bLoop)
		{
			SplinePointsNumber = SplinePointsNumber - 1;
		}

		for (int32 i = 0; i < SplinePointsNumber; i++)
		{
			const int32 IndexCurrent = i;
			int32 IndexNext = IndexCurrent + 1;

			if (i > 0)
			{
				const FName ComponentName = *(FString(TEXT("SMC")).Append(FString::SanitizeFloat(FPlatformTime::Seconds())));
				USplineMeshComponent* SMC = DuplicateObject<USplineMeshComponent>(SplineMeshComponent, this, ComponentName);
				SMC->OnComponentCreated();
				SMC->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				SMC->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
				SMC->RegisterComponent();
				SplineMeshComponents.Insert(SMC, IndexCurrent);
			}

			if (bLoop && (i == SplinePointsNumber - 1))
			{
				IndexNext = 0;
			}

			if (SplineMeshComponents[IndexCurrent])
			{
				//Location
				FVector StartPos;
				FVector StartTangent;
				FVector EndPos;
				FVector EndTangent;
				SplineComponent->GetLocationAndTangentAtSplinePoint(IndexCurrent, StartPos, StartTangent, ESplineCoordinateSpace::Local);
				SplineComponent->GetLocationAndTangentAtSplinePoint(IndexNext, EndPos, EndTangent, ESplineCoordinateSpace::Local);
				SplineMeshComponents[IndexCurrent]->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);

				//Rotation
				const float StartRoll = SplineComponent->GetRotationAtSplinePoint(IndexCurrent, ESplineCoordinateSpace::Local).Roll;
				const float EndRoll = SplineComponent->GetRotationAtSplinePoint(IndexNext, ESplineCoordinateSpace::Local).Roll;
				SplineMeshComponents[IndexCurrent]->SetStartRoll(StartRoll, true);
				SplineMeshComponents[IndexCurrent]->SetEndRoll(EndRoll, true);

				//Scale
				const FVector2D StartScale = FVector2D(SplineComponent->GetScaleAtSplinePoint(IndexCurrent));
				const FVector2D EndScale = FVector2D(SplineComponent->GetScaleAtSplinePoint(IndexNext));
				SplineMeshComponents[IndexCurrent]->SetStartScale(StartScale);
				SplineMeshComponents[IndexCurrent]->SetEndScale(EndScale);
			}
		}
	}
}

void AIPSplineMeshActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	OnConstruction(GetActorTransform());
}
#endif
