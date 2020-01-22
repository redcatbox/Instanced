// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "IPSplineMeshGradientActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPSplineMeshGradientActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
	AIPSplineMeshGradientActor();
	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void RunGeneration() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		USplineMeshComponent* SplineMeshComponent;

	UPROPERTY()
		TArray<USplineMeshComponent*> SplineMeshComponents;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		USplineComponent* SplineComponent;

	/** Should reverse gradient direction? */
	UPROPERTY(EditAnywhere, Category = Generation)
		bool bInverseGradient;
#endif
};
