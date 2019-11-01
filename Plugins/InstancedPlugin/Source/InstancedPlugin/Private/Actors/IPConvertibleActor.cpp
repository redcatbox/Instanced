// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPConvertibleActor.h"
#include "Engine/Selection.h"
#include "Engine/StaticMeshActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Actors/IPTransformsArrayActor.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

//AIPConvertibleActor::AIPConvertibleActor() {}

#if WITH_EDITOR
void AIPConvertibleActor::ConvertToInstances()
{
	USelection* Selection = GEditor->GetSelectedActors();
	TArray<AStaticMeshActor*> StaticMeshActors;
	TArray<UStaticMesh*> StaticMeshes;
	TArray<ULevel*> Levels;
	Levels.AddUnique(this->GetLevel());

	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		if (AStaticMeshActor* SMActor = Cast<AStaticMeshActor>(*Iter))
		{
			StaticMeshActors.Add(SMActor);
			StaticMeshes.AddUnique(SMActor->GetStaticMeshComponent()->GetStaticMesh());
			Levels.AddUnique(SMActor->GetLevel());
		}
	}

	if (Levels.Num() > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected actors are not in the same sublevel! Please select actors from the same sublevel."));
	}
	else if (StaticMeshActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No StaticMeshActors selected! Please select few StaticMeshActors to proceed."));
	}
	else if (StaticMeshes.Num() > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMeshActors have different static meshes! Please select StaticMeshActors with the same static meshes."));
	}
	else
	{
		GEditor->SelectNone(false, true);
		UE_LOG(LogTemp, Warning, TEXT("Processing convertation..."));
		UE_LOG(LogTemp, Warning, TEXT("Note: Material(s) from first selected StaticMeshActor will be used for all instances!"));

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.OverrideLevel = this->GetLevel();
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform = GetActorTransform();
		AActor* Actor = GetWorld()->SpawnActor(AIPTransformsArrayActor::StaticClass(), &SpawnTransform, SpawnInfo);

		if (AIPTransformsArrayActor* TAActor = Cast<AIPTransformsArrayActor>(Actor))
		{
			// Get mesh and material from the first selected static mesh actor
			TAActor->HISMComponent->SetStaticMesh(StaticMeshActors[0]->GetStaticMeshComponent()->GetStaticMesh());
			int32 NumMaterials = StaticMeshActors[0]->GetStaticMeshComponent()->GetNumMaterials();
			for (int32 i = 0; i < NumMaterials; i++)
				TAActor->HISMComponent->SetMaterial(i, StaticMeshActors[0]->GetStaticMeshComponent()->GetMaterial(i));

			TAActor->HISMComponent->Modify();

			for (AStaticMeshActor* SMActor : StaticMeshActors)
			{
				FTransform Transform = SMActor->GetActorTransform();
				Transform = Transform.GetRelativeTransform(TAActor->GetActorTransform());
				TAActor->IPProcedureTransformsArray->PlacementTransforms.Add(Transform);

				// Destroy old static mesh actors
				SMActor->MarkPackageDirty();
				bool WasDestroyed = SMActor->GetWorld()->EditorDestroyActor(SMActor, false);
				checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *SMActor->GetClass()->GetName(), *SMActor->GetActorLabel());
			}

			TAActor->RunGeneration();
			TAActor->IPProcedureTransformsArray->Modify();
			UE_LOG(LogTemp, Log, TEXT("%d StaticMeshActors successfully converted to instances!"), StaticMeshActors.Num());
		}
	}
}

void AIPConvertibleActor::ConvertToStaticMeshes()
{
	USelection* Selection = GEditor->GetSelectedActors();

	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		AActor* SelectedActor = Cast<AActor>(*Iter);
		TArray<UActorComponent*> AComponents = SelectedActor->GetComponentsByClass(UInstancedStaticMeshComponent::StaticClass());

		if (AComponents.Num() > 0)
		{
			GEditor->SelectNone(false, true);
			UE_LOG(LogTemp, Warning, TEXT("Processing convertation..."));

			for (UActorComponent* AComp : AComponents)
			{
				if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(AComp))
				{
					if (ISMComp->GetInstanceCount() > 0)
					{
						// Get mesh and material from ISM component
						UStaticMesh* StaticMesh = ISMComp->GetStaticMesh();
						TArray<UMaterialInterface*> Materials;
						int32 NumMaterials = ISMComp->GetNumMaterials();

						for (int32 i = 0; i < NumMaterials; i++)
						{
							Materials.Add(ISMComp->GetMaterial(i));
						}

						FActorSpawnParameters SpawnInfo;
						SpawnInfo.OverrideLevel = this->GetLevel();
						SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						FName FolderName = *(FString(TEXT("Instanced_"))
							.Append(SelectedActor->GetName())
							.Append(FString(TEXT("_")))
							.Append(ISMComp->GetName()));

						for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
						{
							FTransform Transform;
							ISMComp->GetInstanceTransform(i, Transform);
							Transform *= SelectedActor->GetActorTransform();
							AActor* Actor = GetWorld()->SpawnActor(AStaticMeshActor::StaticClass(), &Transform, SpawnInfo);
							AStaticMeshActor* SMActor = Cast<AStaticMeshActor>(Actor);
							SMActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);

							for (int32 j = 0; j < NumMaterials; j++)
							{
								SMActor->GetStaticMeshComponent()->SetMaterial(j, Materials[j]);
							}

							SMActor->RegisterAllComponents();
							SMActor->SetFolderPath(FolderName);
							SMActor->MarkPackageDirty();
							GEditor->SelectActor(SMActor, true, false);
						}

						// Destroy old static mesh actors
						SelectedActor->MarkPackageDirty();
						bool WasDestroyed = SelectedActor->GetWorld()->EditorDestroyActor(SelectedActor, false);
						checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *SelectedActor->GetClass()->GetName(), *SelectedActor->GetActorLabel());

						UE_LOG(LogTemp, Log, TEXT("%d instances successfully converted to StaticMeshActors!"), ISMComp->GetInstanceCount());
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("No instances found! Nothing to convert."));
					}
				}
			}
		}
	}
}
#endif