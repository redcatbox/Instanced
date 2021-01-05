// redbox, 2021

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IPEFunctionLibrary.generated.h"

UCLASS()
class INSTANCEDPLUGINEDITOR_API UIPEFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	/** Replace selected StaticMeshActors or actors containing StaticMeshComponents with instances */
	UFUNCTION()
		static void ConvertStaticMeshesToInstances();

	/** Replace selected instances with static meshes */
	UFUNCTION()
		static void ConvertInstancesToStaticMeshes();

	/** Check selected actors and instances for containing negative scale values */
	UFUNCTION()
		static void CheckNegativeScale();

	/** Find the average location (centroid) of an array of Actors snapped to specified grid size */
	UFUNCTION()
		static FVector GetLocationArrayAverageWithGridSnapping(const TArray<FVector>& Locations, float GridSize = 100.f);
#endif
};
