// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformsArray.h"
#include "IPTransformsArrayActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPTransformsArrayActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPTransformsArrayActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformsArray* IPOperationTransformsArray;
#endif
};
