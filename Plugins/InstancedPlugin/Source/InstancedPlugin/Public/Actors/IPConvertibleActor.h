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
	/** Convert selected static meshes to instances */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToInstances();

	/** Convert selected instances to static meshes */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToStaticMeshes();
#endif

#if WITH_EDITORONLY_DATA
	/** Should remove original objects after convertation? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Convertation)
		bool bRemoveOriginal;

	UPROPERTY()
		UTextRenderComponent* TextIndicator;
#endif

	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
};