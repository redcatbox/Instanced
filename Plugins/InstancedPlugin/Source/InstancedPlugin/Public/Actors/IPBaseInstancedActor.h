// redbox, 2022

#pragma once

#include "IPBaseGeneratedActor.h"
#include "IPBaseInstancedActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPBaseInstancedActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunGeneration() override;
#endif
};
