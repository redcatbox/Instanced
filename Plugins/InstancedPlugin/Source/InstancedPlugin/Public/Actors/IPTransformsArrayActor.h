// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformsArray.h"
#include "IPTransformsArrayActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPTransformsArrayActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPTransformsArrayActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationTransformsArray* IPOperationTransformsArray;
#endif
};