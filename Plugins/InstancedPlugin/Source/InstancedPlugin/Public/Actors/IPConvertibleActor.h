// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPBaseGeneratedActor.h"
#include "Components/TextRenderComponent.h"
#include "IPConvertibleActor.generated.h"

UCLASS(ClassGroup = (Instanced), HideCategories = (Actor, Collision, Cooking, Input, LOD, Rendering, Replication), AutoExpandCategories = (Convertation))
class INSTANCEDPLUGIN_API AIPConvertibleActor : public AActor
{
	GENERATED_BODY()

public:
	AIPConvertibleActor();

#if WITH_EDITOR
	/** Convert selected StaticMeshActors or actors with StaticMeshComponents to instances */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Convertation | StaticMeshesToInstances")
		virtual void ConvertStaticMeshesToInstances();

	/** Convert selected instances to static meshes */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Convertation | InstancesToStaticMeshes")
		virtual void ConvertInstancesToStaticMeshes();

	/** Check selected actors and instances contain negative scale values */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Checks | NegativeScaleValues")
		virtual void CheckNegativeScaleValues();
#endif

#if WITH_EDITORONLY_DATA
	/** Remove original objects after convertation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Convertation)
		bool bRemoveOriginal;

	UPROPERTY()
		UTextRenderComponent* TextIndicator;
#endif

	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
};