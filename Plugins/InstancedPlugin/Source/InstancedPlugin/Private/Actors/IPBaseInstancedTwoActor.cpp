// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPBaseInstancedTwoActor.h"

AIPBaseInstancedTwoActor::AIPBaseInstancedTwoActor()
{
	HISMComponent1 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent"));
	HISMComponent1->SetupAttachment(RootComponent);
	HISMComponent1->Mobility = EComponentMobility::Static;

	HISMComponent2 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent2"));
	HISMComponent2->SetupAttachment(RootComponent);
	HISMComponent2->Mobility = EComponentMobility::Static;

#if WITH_EDITORONLY_DATA
	Distribution = 0.5f;
	Contribution1 = 1.f;
	Contribution2 = 1.f;

	bRandomizeInstances = false;
	bUseRandomStream = false;
	RandomStreamSeed = 0;
	RandomStream.Initialize(RandomStreamSeed);
#endif
}

#if WITH_EDITOR
void AIPBaseInstancedTwoActor::RunGeneration() {}

void AIPBaseInstancedTwoActor::DistributeToTwoTransforms(TArray<FTransform>& Transforms, TArray<FTransform>& Transforms1, TArray<FTransform>& Transforms2)
{
	TArray<FTransform> TransformsRandom = Transforms;

	if (bRandomizeInstances)
	{
		UIPFunctionLibrary::ShuffleArray(TransformsRandom, bUseRandomStream, RandomStream);
	}

	for (int32 i = 0; i < InstancesNum1; i++)
	{
		Transforms1.Add(TransformsRandom[i]);
	}

	for (int32 i = 0; i < InstancesNum2; i++)
	{
		Transforms2.Add(TransformsRandom[TransformsRandom.Num() - 1 - i]);
	}
}

void AIPBaseInstancedTwoActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InstancesNum1 = 100 * Distribution * Contribution1;
	InstancesNum2 = 100 * (1 - Distribution) * Contribution2;

	if (Contribution1 == Contribution2 == 1 && InstancesNum1 + InstancesNum2 != 100)
	{
		InstancesNum2 += 1;
	}

	RandomStream.Initialize(RandomStreamSeed);

	RunGeneration();
}
#endif