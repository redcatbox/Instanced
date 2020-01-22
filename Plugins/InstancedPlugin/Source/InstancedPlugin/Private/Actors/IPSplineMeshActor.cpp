// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPSplineMeshActor.h"

AIPSplineMeshActor::AIPSplineMeshActor()
{
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMeshComponent1"));
	SplineMeshComponent->SetupAttachment(RootComponent);
	SplineMeshComponent->Mobility = EComponentMobility::Static;

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
	RunGeneration();
#endif

	RegisterAllComponents();
}

#if WITH_EDITOR
void AIPSplineMeshActor::RunGeneration()
{
	int32 SplinePointsNumber = SplineComponent->GetNumberOfSplinePoints();
	bool bLoop = SplineComponent->IsClosedLoop();

	if (SplineMeshComponents.Num() > 1)
	{
		for (int32 i = 1; i < SplineMeshComponents.Num(); i++)
		{
			SplineMeshComponents[i]->UnregisterComponent();
			SplineMeshComponents[i]->DestroyComponent();
		}
	}

	SplineMeshComponents.Empty();

	if (!bLoop)
	{
		SplinePointsNumber = SplinePointsNumber - 1;
	}

	for (int32 i = 0; i < SplinePointsNumber; i++)
	{
		//Create new component
		int32 IndexCurrent = i;
		int32 IndexNext = IndexCurrent + 1;
		FName ComponentName = *(FString(TEXT("SplineMeshComponent")).Append(FString::SanitizeFloat(FPlatformTime::Seconds())));

		if (i == 0)
		{
			SplineMeshComponents.Add(SplineMeshComponent);
		}
		else
		{
			SplineMeshComponents.Insert(DuplicateObject<USplineMeshComponent>(SplineMeshComponent, this, ComponentName), IndexCurrent);
			SplineMeshComponents[i]->SetupAttachment(RootComponent);
			SplineMeshComponents[i]->RegisterComponent();
		}

		if (bLoop && i == SplinePointsNumber - 1)
		{
			IndexNext = 0;
		}

		//Location
		FVector StartPos;
		FVector StartTangent;
		FVector EndPos;
		FVector EndTangent;
		SplineComponent->GetLocationAndTangentAtSplinePoint(IndexCurrent, StartPos, StartTangent, ESplineCoordinateSpace::Local);
		SplineComponent->GetLocationAndTangentAtSplinePoint(IndexNext, EndPos, EndTangent, ESplineCoordinateSpace::Local);
		SplineMeshComponents[IndexCurrent]->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);

		//Rotation
		float StartRoll = SplineComponent->GetRotationAtSplinePoint(IndexCurrent, ESplineCoordinateSpace::Local).Roll;
		float EndRoll = SplineComponent->GetRotationAtSplinePoint(IndexNext, ESplineCoordinateSpace::Local).Roll;
		SplineMeshComponents[IndexCurrent]->SetStartRoll(StartRoll, true);
		SplineMeshComponents[IndexCurrent]->SetEndRoll(EndRoll, true);

		//Scale
		FVector2D StartScale = FVector2D(SplineComponent->GetScaleAtSplinePoint(IndexCurrent));
		FVector2D EndScale = FVector2D(SplineComponent->GetScaleAtSplinePoint(IndexNext));
		SplineMeshComponents[IndexCurrent]->SetStartScale(StartScale);
		SplineMeshComponents[IndexCurrent]->SetEndScale(EndScale);
	}

	//for (auto& Obj : SplineMeshComponents)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("name = %s"), *Obj->GetName());
	//}
}

void AIPSplineMeshActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PropertyName == TEXT("Transform"))
	{
		OnConstruction(this->GetActorTransform());
	}
}
#endif