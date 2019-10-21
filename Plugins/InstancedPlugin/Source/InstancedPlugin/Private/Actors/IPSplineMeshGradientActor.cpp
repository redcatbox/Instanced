// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSplineMeshGradientActor.h"
#include "Materials/MaterialInstanceDynamic.h"

AIPSplineMeshGradientActor::AIPSplineMeshGradientActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMeshComponent1"));
	SplineMeshComponent->SetupAttachment(RootComponent);
	SplineMeshComponent->Mobility = EComponentMobility::Static;

#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;

	bInverseGradient = false;
#endif
}

void AIPSplineMeshGradientActor::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	RunGeneration();
#endif

	RegisterAllComponents();
}

#if WITH_EDITOR
void AIPSplineMeshGradientActor::RunGeneration()
{
	int32 SplinePointsNumber = SplineComponent->GetNumberOfSplinePoints();
	bool bLoop = SplineComponent->IsClosedLoop();

	if (SplineMeshComponents.Num() > 1)
		for (int32 i = 1; i < SplineMeshComponents.Num(); i++)
		{
			SplineMeshComponents[i]->UnregisterComponent();
			SplineMeshComponents[i]->DestroyComponent();
		}

	SplineMeshComponents.Empty();

	if (!bLoop)
		SplinePointsNumber = SplinePointsNumber - 1;

	if (SplineMeshComponent->GetStaticMesh())
		for (int32 i = 0; i < SplinePointsNumber; i++)
		{
			//Create new component
			int32 IndexCurrent = i;
			int32 IndexNext = IndexCurrent + 1;
			FName ComponentName = *(FString(TEXT("SplineMeshComponent")).Append(FString::SanitizeFloat(FPlatformTime::Seconds())));

			if (i == 0)
				SplineMeshComponents.Add(SplineMeshComponent);
			else
			{
				SplineMeshComponents.Insert(DuplicateObject<USplineMeshComponent>(SplineMeshComponent, this, ComponentName), IndexCurrent);
				SplineMeshComponents[i]->SetupAttachment(RootComponent);
				SplineMeshComponents[i]->RegisterComponent();
				//SplineMeshComponents[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, NAME_None);
			}

			if (bLoop && i == SplinePointsNumber - 1)
				IndexNext = 0;

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

			//Meshes Gradients
			float SplineLength = SplineComponent->GetSplineLength();

			for (int32 j = 0; j < SplineMeshComponents[IndexCurrent]->GetNumMaterials(); j++)
			{
				UMaterialInterface* Material = SplineMeshComponents[IndexCurrent]->GetMaterial(j);

				if (Material)
				{
					UMaterialInstanceDynamic* MID = SplineMeshComponents[IndexCurrent]->CreateDynamicMaterialInstance(j, Material);
					float GradientStart = bInverseGradient ? 
						SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexCurrent) / SplineLength : 1.f - SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexCurrent) / SplineLength;
					float GradientEnd = bInverseGradient ? 
						SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexNext) / SplineLength : 1.f - SplineComponent->GetDistanceAlongSplineAtSplinePoint(IndexNext) / SplineLength;
					MID->SetScalarParameterValue(TEXT("GradientStart"), GradientStart);
					MID->SetScalarParameterValue(TEXT("GradientEnd"), GradientEnd);
				}
			}
		}

	//for (auto& Obj : SplineMeshComponents)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("name = %s"), *Obj->GetName());
	//}
}

void AIPSplineMeshGradientActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("Transform") || TEXT("bInverseGradient"))
		OnConstruction(this->GetActorTransform());
}
#endif