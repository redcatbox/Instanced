// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPConvertibleActor.h"
#include "Engine/Selection.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Actors/IPTransformsArrayActor.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

AIPConvertibleActor::AIPConvertibleActor()
{
	// Default root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DefaultSceneRoot->Mobility = EComponentMobility::Static;

#if WITH_EDITORONLY_DATA
	DefaultSceneRoot->bVisualizeComponent = true;
	bIsEditorOnlyActor = true;
	bRemoveOriginal = true;

	TextIndicator = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextIndicator"));
	TextIndicator->SetupAttachment(RootComponent);
	TextIndicator->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	TextIndicator->SetText(FText::FromString("Convertible"));
	TextIndicator->bAlwaysRenderAsText = true;
	TextIndicator->bHiddenInGame = true;
	TextIndicator->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextIndicator->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	TextIndicator->SetWorldSize(50.f);
	TextIndicator->SetTextRenderColor(FColor::White);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TextMaterialObj(TEXT("/InstancedPlugin/Materials/UnlitText.UnlitText"));
	if (TextMaterialObj.Object)
	{
		TextIndicator->SetTextMaterial(TextMaterialObj.Object);
	}
#endif
}

#if WITH_EDITOR
void AIPConvertibleActor::ConvertStaticMeshesToInstances()
{
	USelection* Selection = GEditor->GetSelectedActors();
	TArray<UStaticMeshComponent*> ProcessedSMComps;
	TArray<UStaticMesh*> SMs;
	TArray<ULevel*> Levels;
	TArray < AIPTransformsArrayActor*> IPTAActors;
	TArray<AActor*> OriginalActorsToDestroy;

	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		if (AActor* SelectedActor = Cast<AActor>(*Iter))
		{
			TArray<UActorComponent*> AComponents;
			SelectedActor->GetComponents(UStaticMeshComponent::StaticClass(), AComponents);

			if (AComponents.Num() > 0)
			{
				for (UActorComponent* AComp : AComponents)
				{
					UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(AComp);
					if (!ISMComp)
					{
						UStaticMeshComponent* SMComp = Cast<UStaticMeshComponent>(AComp);
						UStaticMesh* SM = SMComp->GetStaticMesh();

						if (SMComp && SM)
						{
							ProcessedSMComps.Add(SMComp);
							SMs.AddUnique(SM);
							Levels.AddUnique(SelectedActor->GetLevel());
						}
					}
				}
			}
		}
	}

	if (ProcessedSMComps.Num() > 0 && SMs.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Processing convertation. Material(s) from first found StaticMeshComponent will be used for all instances!"));
		GEditor->SelectNone(false, true);

		for (ULevel* Level : Levels)
		{
			for (UStaticMesh* SM : SMs)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.OverrideLevel = Level;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FTransform SpawnTransform = this->GetActorTransform();
				AActor* Actor = GetWorld()->SpawnActor(AIPTransformsArrayActor::StaticClass(), &SpawnTransform, SpawnInfo);
				AIPTransformsArrayActor* IPTAActor = Cast<AIPTransformsArrayActor>(Actor);
				IPTAActors.AddUnique(IPTAActor);

				for (UStaticMeshComponent* SMComp : ProcessedSMComps)
				{
					if (Level == SMComp->GetOwner()->GetLevel() && SM == SMComp->GetStaticMesh())
					{
						IPTAActor->HISMComponent->SetStaticMesh(SM);
						int32 NumMaterials = SMComp->GetNumMaterials();

						for (int32 i = 0; i < NumMaterials; i++)
						{
							IPTAActor->HISMComponent->SetMaterial(i, SMComp->GetMaterial(i));
						}

						FTransform Transform = SMComp->GetComponentTransform();

						if (Transform.GetScale3D().GetMin() < 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent %s contains negative scale values!"), *SMComp->GetName());
						}

						Transform = Transform.GetRelativeTransform(IPTAActor->GetActorTransform());
						IPTAActor->IPProcedureTransformsArray->PlacementTransforms.Add(Transform);
					}

					if (bRemoveOriginal)
					{
						OriginalActorsToDestroy.AddUnique(SMComp->GetOwner());
					}
				}

				if (bRemoveOriginal)
				{
					for (AActor* ActorToDestroy : OriginalActorsToDestroy)
					{
						ActorToDestroy->MarkPackageDirty();
						bool WasDestroyed = ActorToDestroy->GetWorld()->EditorDestroyActor(ActorToDestroy, false);
						checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ActorToDestroy->GetName(), *ActorToDestroy->GetActorLabel());
					}
				}
			}
		}

		if (IPTAActors.Num() > 0)
		{
			for (AIPTransformsArrayActor* IPTAActor : IPTAActors)
			{
				IPTAActor->RunGeneration();
			}

			UE_LOG(LogTemp, Warning, TEXT("%d StaticMeshComponents successfully converted to instances."), ProcessedSMComps.Num());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No StaticMeshComponents or valid StaticMesh properties found. Nothing to convert."));
		UE_LOG(LogTemp, Warning, TEXT("Convertation aborted."));
	}
}

void AIPConvertibleActor::ConvertInstancesToStaticMeshes()
{
	//USelection* Selection = GEditor->GetSelectedActors();
	//TArray<AActor*> SelectedActors;
	//TArray<UInstancedStaticMeshComponent*> ISMComponents;
	//TArray<ULevel*> Levels;
	//Levels.AddUnique(this->GetLevel());

	//for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	//{
	//	if (AActor* SelectedActor = Cast<AActor>(*Iter))
	//	{
	//		SelectedActors.Add(SelectedActor);
	//		Levels.AddUnique(SelectedActor->GetLevel());
	//	}
	//}

	//if (Levels.Num() != 1)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Selected actors are not in the same sublevel! Please select actors from the same sublevel."));
	//	UE_LOG(LogTemp, Warning, TEXT("Convertation aborted."));
	//	return;
	//}

	//for (AActor* SelectedActor : SelectedActors)
	//{
	//	TArray<UActorComponent*> AComponents;
	//	SelectedActor->GetComponents(UInstancedStaticMeshComponent::StaticClass(), AComponents);

	//	if (AComponents.Num() > 0)
	//	{
	//		for (UActorComponent* AComp : AComponents)
	//		{
	//			if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(AComp))
	//			{
	//				ISMComponents.Add(ISMComp);
	//			}
	//		}
	//	}
	//}

	//if (ISMComponents.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("No ISM components found in selected actors!"));
	//	UE_LOG(LogTemp, Warning, TEXT("Convertation aborted."));
	//}
	//else
	//{
	//	GEditor->SelectNone(false, true);
	//	UE_LOG(LogTemp, Warning, TEXT("Processing convertation. %d ISM components found."), ISMComponents.Num());

	//	for (UInstancedStaticMeshComponent* ISMComp : ISMComponents)
	//	{
	//		if (ISMComp->GetInstanceCount() > 0)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Converting %s with %d instances."), *ISMComp->GetName(), ISMComp->GetInstanceCount());
	//			UStaticMesh* StaticMesh = ISMComp->GetStaticMesh();
	//			TArray<UMaterialInterface*> Materials;
	//			int32 NumMaterials = ISMComp->GetNumMaterials();

	//			for (int32 i = 0; i < NumMaterials; i++)
	//			{
	//				Materials.Add(ISMComp->GetMaterial(i));
	//			}

	//			FActorSpawnParameters SpawnInfo;
	//			SpawnInfo.OverrideLevel = this->GetLevel();
	//			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//			FName FolderName = *(FString(TEXT("Instanced_"))
	//				.Append(ISMComp->GetOwner()->GetName())
	//				.Append(FString(TEXT("_")))
	//				.Append(ISMComp->GetName()));

	//			for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
	//			{
	//				FTransform Transform;
	//				ISMComp->GetInstanceTransform(i, Transform);
	//				Transform *= ISMComp->GetComponentTransform();
	//				AActor* Actor = GetWorld()->SpawnActor(AStaticMeshActor::StaticClass(), &Transform, SpawnInfo);
	//				AStaticMeshActor* SMActor = Cast<AStaticMeshActor>(Actor);
	//				SMActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);

	//				for (int32 j = 0; j < NumMaterials; j++)
	//				{
	//					SMActor->GetStaticMeshComponent()->SetMaterial(j, Materials[j]);
	//				}

	//				SMActor->RegisterAllComponents();
	//				SMActor->SetFolderPath(FolderName);
	//				SMActor->MarkPackageDirty();
	//				GEditor->SelectActor(SMActor, true, false);
	//			}

	//			if (bRemoveOriginal)
	//			{
	//				ISMComp->GetOwner()->MarkPackageDirty();
	//				bool WasDestroyed = ISMComp->GetOwner()->GetWorld()->EditorDestroyActor(ISMComp->GetOwner(), false);
	//				checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ISMComp->GetOwner()->GetName(), *ISMComp->GetOwner()->GetActorLabel());
	//			}

	//			UE_LOG(LogTemp, Warning, TEXT("%d instances successfully converted to StaticMeshActors!"), ISMComp->GetInstanceCount());
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("No instances found in actor %s (%s)! Nothing to convert."), ISMComp->GetOwner()->GetName(), ISMComp->GetName());
	//		}
	//	}
	//}
}

void AIPConvertibleActor::CheckNegativeScaleValues()
{
	USelection* Selection = GEditor->GetSelectedActors();
	TArray<UStaticMeshComponent*> ProcessedSMComps;

	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		if (AActor* SelectedActor = Cast<AActor>(*Iter))
		{
			TArray<UActorComponent*> AComponents;
			SelectedActor->GetComponents(UStaticMeshComponent::StaticClass(), AComponents);

			if (AComponents.Num() > 0)
			{
				for (UActorComponent* AComp : AComponents)
				{
					if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(AComp))
					{
						if (ISMComp->GetInstanceCount() > 0)
						{
							for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
							{
								FTransform InstanceTransf;
								ISMComp->GetInstanceTransform(i, InstanceTransf);
								if (InstanceTransf.GetScale3D().GetMin() < 0)
								{
									UE_LOG(LogTemp, Warning, TEXT("Level = %s, Actor = %s, InstancedStaticMeshComponent = %s, InstanceId = %d, Scale3D = (%s)"), *SelectedActor->GetLevel()->GetName(), *SelectedActor->GetName(), *ISMComp->GetName(), i, *InstanceTransf.GetScale3D().ToString());
								}
							}
						}
					}
					else if (UStaticMeshComponent* SMComp = Cast<UStaticMeshComponent>(AComp))
					{
						FVector CompScale = SMComp->GetComponentTransform().GetScale3D();
						if (CompScale.GetMin() < 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("Level = %s, Actor = %s, StaticMeshComponent = %s, Scale3D = (%s)"), *SelectedActor->GetLevel()->GetName(), *SelectedActor->GetName(), *SMComp->GetName(), *CompScale.ToString());
						}
					}
				}
			}
		}
	}
}
#endif