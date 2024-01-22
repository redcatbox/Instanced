// redbox, 2022

#include "Objects/IPFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

#if WITH_EDITOR
// Random
void UIPFunctionLibrary::MutateRandomSeed(FRandomStream& RandomStream)
{
	RandomStream.Initialize((RandomStream.GetCurrentSeed() * 196314165) + 907633515);
}

void UIPFunctionLibrary::ShuffleArray(TArray<FTransform>& Array, bool bFromStream, FRandomStream& RandomStream)
{
	const int32 LastIndex = Array.Num() - 1;

	if (bFromStream)
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			const int32 Index = RandomStream.RandRange(i, LastIndex);
			if (i != Index)
			{
				Array.SwapMemory(i, Index);
			}
		}
	else
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			const int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Array.SwapMemory(i, Index);
			}
		}
}


// Vectors
FVector UIPFunctionLibrary::RandomVectorInDelta(FVector DeltaVector, bool bPositiveOnly, bool bUseRandomStream, FRandomStream RandomStream)
{
	const float Min = bPositiveOnly ? 0.f : -1.f;
	const float Max = 1.f;
	TArray<float> Values;

	for (int32 i = 0; i < 3; i++)
	{
		const float Value = bUseRandomStream
			? UKismetMathLibrary::RandomFloatInRangeFromStream(RandomStream, Min, Max)
			: UKismetMathLibrary::RandomFloatInRange(Min, Max);

		Values.Add(Value);
	}

	return DeltaVector * FVector(Values[0], Values[1], Values[2]);
}

FVector UIPFunctionLibrary::RandomVectorInMinMax(FVector VectorMin, FVector VectorMax, bool bUseRandomStream, FRandomStream RandomStream)
{
	return VectorMin + UIPFunctionLibrary::RandomVectorInDelta(VectorMax - VectorMin, true, bUseRandomStream, RandomStream);
}

FVector UIPFunctionLibrary::ClampVector(FVector Vector, FVector VectorMin, FVector VectorMax)
{
	return FVector(
		FMath::Clamp(Vector.X, VectorMin.X, VectorMax.X),
		FMath::Clamp(Vector.Y, VectorMin.Y, VectorMax.Y),
		FMath::Clamp(Vector.Z, VectorMin.Z, VectorMax.Z));
}

FVector UIPFunctionLibrary::AbsVector(FVector Vector)
{
	return Vector.GetAbs();
}


// Rotators
FRotator UIPFunctionLibrary::RandomRotatorInDelta(FRotator DeltaRotator, bool bPositiveOnly, bool bUseRandomStream, FRandomStream RandomStream)
{
	const float Min = bPositiveOnly ? 0.f : -1.f;
	const float Max = 1.f;
	TArray<float> Values;

	for (int32 i = 0; i < 3; i++)
	{
		const float Value = bUseRandomStream
			? UKismetMathLibrary::RandomFloatInRangeFromStream(RandomStream, Min, Max)
			: UKismetMathLibrary::RandomFloatInRange(Min, Max);

		Values.Add(Value);
	}

	return FRotator(DeltaRotator.Pitch * Values[0], DeltaRotator.Yaw * Values[1], DeltaRotator.Roll * Values[2]);
}

FRotator UIPFunctionLibrary::RandomRotatorInMinMax(FRotator RotatorMin, FRotator RotatorMax, bool bUseRandomStream, FRandomStream RandomStream)
{
	return RotatorMin + UIPFunctionLibrary::RandomRotatorInDelta(UKismetMathLibrary::NormalizedDeltaRotator(RotatorMax, RotatorMin), true, bUseRandomStream, RandomStream);
}

FRotator UIPFunctionLibrary::ClampRotator(FRotator Rotator, FRotator RotatorMin, FRotator RotatorMax)
{
	return FRotator(
		FMath::Clamp(Rotator.Pitch, RotatorMin.Pitch, RotatorMax.Pitch),
		FMath::Clamp(Rotator.Yaw, RotatorMin.Yaw, RotatorMax.Yaw),
		FMath::Clamp(Rotator.Roll, RotatorMin.Roll, RotatorMax.Roll));
}
#endif
