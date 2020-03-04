// Dmitriy Barannik aka redbox, 2020

/** https://en.wikipedia.org/wiki/Archimedean_spiral */

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationSpiral.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationSpiral : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationSpiral();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Initial spiral velocity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		FVector InitialLinearVelocity;

	/** Linear acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		FVector LinearAcceleration;

	/** Angular velocity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		FVector AngularVelocity;

	/** Time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		float Time;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bOrientToCentralAxis;
#endif
};