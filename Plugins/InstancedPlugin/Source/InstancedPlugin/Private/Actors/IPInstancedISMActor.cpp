// redbox, 2022

#include "Actors/IPInstancedISMActor.h"

AIPInstancedISMActor::AIPInstancedISMActor()
{
	InstancedStaticMeshComponentClass = UInstancedStaticMeshComponent::StaticClass();
	ISMComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMComponent"));
	ISMComponent->Mobility = EComponentMobility::Static;
	ISMComponent->SetupAttachment(RootComponent);
}

#if WITH_EDITOR
void AIPInstancedISMActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("InstancedStaticMeshComponentClass"))
	{
		UStaticMesh* StaticMesh = ISMComponent->GetStaticMesh();
		TArray<UMaterialInterface*> Materials = ISMComponent->GetMaterials();
		TArray<USceneComponent*> ChildComponents;
		ISMComponent->GetChildrenComponents(false, ChildComponents);

		ISMComponent = NewObject<UInstancedStaticMeshComponent>(this, InstancedStaticMeshComponentClass);
		ISMComponent->Mobility = EComponentMobility::Static;
		ISMComponent->RegisterComponent();
		ISMComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		ISMComponent->SetStaticMesh(StaticMesh);
		for (int32 i = 0; i < Materials.Num(); i++)
		{
			ISMComponent->SetMaterial(i, Materials[i]);
		}

		for (USceneComponent* ChildComponent : ChildComponents)
		{
			ChildComponent->AttachToComponent(ISMComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif