// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "IPFunctionLibrary.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API UIPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	/** Generate new random seed for provided random stream */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static void MutateRandomSeed(FRandomStream& RandomStream);

	/** Generate new random seed for provided random stream */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static void ShuffleArray(TArray<FTransform>& Array, bool bFromStream, FRandomStream& RandomStream);

	/** Get random vector in delta vector */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FVector RandomVectorInDelta(FVector DeltaVector, bool bPositiveOnly, bool bUseRandomStream, FRandomStream RandomStream);

	/** Get random vector between min and max vectors */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FVector RandomVectorInMinMax(FVector VectorMin, FVector VectorMax, bool bUseRandomStream, FRandomStream RandomStream);

	/** Clamp vector between min and max vectors */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FVector ClampVector(FVector Vector, FVector VectorMin, FVector VectorMax);

	/** Get vector with absolute values */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FVector AbsVector(FVector Vector);

	/** Get random rotator in delta rotator */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FRotator RandomRotatorInDelta(FRotator DeltaRotator, bool bPositiveOnly, bool bUseRandomStream, FRandomStream RandomStream);

	/** Get random rotator between min and max rotators */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FRotator RandomRotatorInMinMax(FRotator RotatorMin, FRotator RotatorMax, bool bUseRandomStream, FRandomStream RandomStream);
	
	/** Clamp rotator between min and max rotators */
	UFUNCTION(BlueprintCallable, Category = "InstancedPlugin")
		static FRotator ClampRotator(FRotator Rotator, FRotator RotatorMin, FRotator RotatorMax);
#endif
};
