// redbox, 2023

#pragma once

#include "IPBaseGeneratedActor.h"
#include "ProceduralMeshComponent.h"
#include "IPSplineProceduralMeshActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSplineProceduralMeshActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
	AIPSplineProceduralMeshActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	class UProceduralMeshComponent* ProceduralMeshComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	class USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, Category = Operation)
	bool bLinearSpline;

	UPROPERTY(EditAnywhere, Category = Operation)
	bool bFromSplinePoints;

	UPROPERTY(EditAnywhere, Category = Operation, Meta = (ClampMin = "0", UIMin = "0", EditCondition = "!bFromSplinePoints"))
	int32 SplineSubdivisions;

	UPROPERTY(EditAnywhere, Category = Operation)
	bool bFlipNormal;

	UPROPERTY(EditAnywhere, Category = Operation)
	bool bCreateCollision;
#endif

#if WITH_EDITOR
	virtual void RunGeneration() override;
	bool TriangulatePoly(TArray<int32>& OutTris, const TArray<FProcMeshVertex>& PolyVerts, const FVector3f& PolyNormal);
#endif
};
