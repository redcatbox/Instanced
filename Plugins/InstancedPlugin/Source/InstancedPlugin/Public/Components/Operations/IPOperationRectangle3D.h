// redbox, 2022

#pragma once

#include "IPOperationGrid3DBase.h"
#include "IPOperationRectangle3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationRectangle3D : public UIPOperationGrid3DBase
{
	GENERATED_BODY()

public:
	UIPOperationRectangle3D();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Create corner meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bCornersMeshes;

	/** Orient corner meshes around the object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bOrientCornersMeshesAround;

	/** Create sides meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bSidesMeshes;

	/** Orient sides meshes outside */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bOrientSidesMeshesOutside;

	/** Orient sides meshes inside */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bOrientSidesMeshesOutside"))
	bool bReverseSidesMeshesOrientation;
#endif
};
