// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureRandomTransform.h"

UIPProcedureRandomTransform::UIPProcedureRandomTransform()
{
#if WITH_EDITORONLY_DATA
	bRandomLocation = false;
	RandomLocationMin = FVector::ZeroVector;
	RandomLocationMax = FVector::ZeroVector;

	bRandomRotation = false;
	RandomRotationMin = FRotator(0.f, 0.f, 0.f);
	RandomRotationMax = FRotator(0.f, 0.f, 0.f);

	bRandomRotationByFixedRotatorSteps = false;
	bRandomRotationByFixedRotatorStepsEditCondition = bRandomRotation && bRandomRotationByFixedRotatorSteps;
	FixedRotator = FRotator(0.f, 0.f, 0.f);
	StepsMin = 0;
	StepsMax = 1;

	bRandomScale = false;
	bRandomizeScaleUniformly = false;
	RandomScaleMin = FVector::OneVector;
	RandomScaleMax = FVector::OneVector;
#endif
}

#if WITH_EDITOR
FVector UIPProcedureRandomTransform::RandomizeLocation(FVector Location)
{
	UIPFunctionLibrary::MutateRandomSeed(RandomStream);
	return Location + UIPFunctionLibrary::RandomVectorInMinMax(RandomLocationMin, RandomLocationMax, bUseRandomStream, RandomStream);
}

FRotator UIPProcedureRandomTransform::RandomizeRotation(FRotator Rotation)
{
	UIPFunctionLibrary::MutateRandomSeed(RandomStream);
	return Rotation + UIPFunctionLibrary::RandomRotatorInMinMax(RandomRotationMin, RandomRotationMax, bUseRandomStream, RandomStream);
}

// Rotation by fixed rotator steps
FRotator UIPProcedureRandomTransform::RandomizeRotationByFixedRotatorSteps(FRotator Rotation)
{
	UIPFunctionLibrary::MutateRandomSeed(RandomStream);
	int32 Steps = FMath::RandRange(StepsMin, StepsMax);

	if (bUseRandomStream)
	{
		Steps = RandomStream.RandRange(StepsMin, StepsMax);
	}

	return Rotation + FixedRotator * Steps;
}

FVector UIPProcedureRandomTransform::RandomizeScale(FVector Scale)
{
	UIPFunctionLibrary::MutateRandomSeed(RandomStream);
	FVector NewScale = UIPFunctionLibrary::RandomVectorInMinMax(RandomScaleMin, RandomScaleMax, bUseRandomStream, RandomStream);

	if (bRandomizeScaleUniformly)
	{
		return Scale * FVector(NewScale.X, NewScale.X, NewScale.X);
	}
	else
	{
		return Scale * NewScale;
	}
}

void UIPProcedureRandomTransform::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);

	RandomLocationMax = FVector(
		FMath::Clamp(RandomLocationMax.X, RandomLocationMin.X, RandomLocationMax.X),
		FMath::Clamp(RandomLocationMax.Y, RandomLocationMin.Y, RandomLocationMax.Y),
		FMath::Clamp(RandomLocationMax.Z, RandomLocationMin.Z, RandomLocationMax.Z));

	RandomRotationMax = FRotator(
		FMath::Clamp(RandomRotationMax.Pitch, RandomRotationMin.Pitch, RandomRotationMax.Pitch),
		FMath::Clamp(RandomRotationMax.Yaw, RandomRotationMin.Yaw, RandomRotationMax.Yaw),
		FMath::Clamp(RandomRotationMax.Roll, RandomRotationMin.Roll, RandomRotationMax.Roll));

	RandomScaleMax = FVector(
		FMath::Clamp(RandomScaleMax.X, RandomScaleMin.X, RandomScaleMax.X),
		FMath::Clamp(RandomScaleMax.Y, RandomScaleMin.Y, RandomScaleMax.Y),
		FMath::Clamp(RandomScaleMax.Z, RandomScaleMin.Z, RandomScaleMax.Z));

	bRandomRotationByFixedRotatorStepsEditCondition = bRandomRotation && bRandomRotationByFixedRotatorSteps;
	StepsMin = FMath::Clamp(StepsMin, 1, StepsMax);
	StepsMax = FMath::Clamp(StepsMax, StepsMin, StepsMax);

	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		for (int32 i = 0; i < InstancesNum; i++)
		{
			FVector Location = Transf.GetLocation();
			FRotator Rotation = Transf.Rotator();
			FVector Scale = Transf.GetScale3D();

			if (bRandomLocation)
			{
				Location = RandomizeLocation(Location);
			}

			if (bRandomRotation)
			{
				Rotation = RandomizeRotation(Rotation);
			}

			if (bRandomRotationByFixedRotatorSteps)
			{
				Rotation = RandomizeRotationByFixedRotatorSteps(Rotation);
			}

			if (bRandomScale)
			{
				Scale = RandomizeScale(Scale);
			}

			ResultTransforms.Add(FTransform(Rotation, Location, Scale));
		}
	}

	Transforms = ResultTransforms;
}
#endif