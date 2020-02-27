// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
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
#endif
};
