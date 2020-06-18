// redbox, 2020

#pragma once

#include "Actors/IPSplineMeshActor.h"
#include "IPSplineMeshGradientActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSplineMeshGradientActor : public AIPSplineMeshActor
{
	GENERATED_BODY()

public:
	AIPSplineMeshGradientActor();

#if WITH_EDITOR
	virtual void RunGeneration() override;

	UFUNCTION(BlueprintCallable, Category = "Generation")
		virtual void GenerateSplineGradient();
#endif

#if WITH_EDITORONLY_DATA
	/** Should reverse gradient direction? */
	UPROPERTY(EditAnywhere, Category = "Generation")
		bool bInverseGradient;
#endif
};