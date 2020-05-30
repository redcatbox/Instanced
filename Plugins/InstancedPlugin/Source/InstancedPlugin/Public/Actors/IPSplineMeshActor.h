// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "IPSplineMeshActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSplineMeshActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
	AIPSplineMeshActor();
	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void RunGeneration() override;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USplineComponent* SplineComponent;
#endif

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USplineMeshComponent* SplineMeshComponent;

	UPROPERTY(TextExportTransient)
		TArray<USplineMeshComponent*> SplineMeshComponents;
};
