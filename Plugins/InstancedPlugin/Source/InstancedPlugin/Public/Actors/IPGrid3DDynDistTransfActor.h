// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPGrid3DActor.h"
#include "Components/Procedures/IPProcedureDynamicTransform.h"
#include "IPGrid3DDynDistTransfActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPGrid3DDynDistTransfActor : public AIPGrid3DActor
{
	GENERATED_BODY()

public:
	AIPGrid3DDynDistTransfActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureDynamicTransform* IPProcedureDynamicTransform;
};
