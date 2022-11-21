// redbox, 2022

#include "Objects/IPEFunctionLibrary.h"
#include "InstancedPluginEditor.h"
#include "Engine/Selection.h"
#include "Engine/StaticMeshActor.h"
#include "Actors/IPTransformsArrayActor.h"
#include "Editor/GroupActor.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#if WITH_EDITOR
// Convertation
void UIPEFunctionLibrary::ConvertStaticMeshesToInstances()
{
	USelection* Selection = GEditor->GetSelectedActors();
	TArray<UStaticMeshComponent*> ProcessedSMComps;
	TArray<UStaticMesh*> SMs;
	TArray<ULevel*> Levels;
	TArray<AIPTransformsArrayActor*> IPTAActors;
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
		UE_LOG(IPELog, Warning, TEXT("Processing convertation."));
		GEditor->SelectNone(false, true);

		for (ULevel* Level : Levels)
		{
			for (UStaticMesh* SM : SMs)
			{
				TArray<UStaticMeshComponent*> SMComps;
				TArray<FVector> Locations;

				for (UStaticMeshComponent* SMComp : ProcessedSMComps)
				{
					if (Level == SMComp->GetOwner()->GetLevel() && SM == SMComp->GetStaticMesh())
					{
						SMComps.Add(SMComp);
						Locations.Add(SMComp->GetComponentTransform().GetLocation());
						OriginalActorsToDestroy.AddUnique(SMComp->GetOwner());
					}
				}

				FActorSpawnParameters SpawnInfo;
				SpawnInfo.OverrideLevel = Level;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FTransform SpawnTransform = FTransform();
				FVector SpawnLocation = UIPEFunctionLibrary::GetLocationArrayAverageWithGridSnapping(Locations);
				SpawnTransform.SetLocation(SpawnLocation);
				AActor* Actor = Level->GetWorld()->SpawnActor(AIPTransformsArrayActor::StaticClass(), &SpawnTransform, SpawnInfo);
				AIPTransformsArrayActor* IPTAActor = Cast<AIPTransformsArrayActor>(Actor);
				IPTAActors.AddUnique(IPTAActor);

				if (SMComps.Num() > 0)
				{
					IPTAActor->ISMComponent->SetStaticMesh(SM);
					UE_LOG(IPELog, Warning, TEXT("Material(s) from first found StaticMeshComponent will be used for all instances with the same static mesh!"));

					for (int32 i = 0; i < SMComps[0]->GetNumMaterials(); i++)
					{
						IPTAActor->ISMComponent->SetMaterial(i, SMComps[0]->GetMaterial(i));
					}
				}

				for (UStaticMeshComponent* SMComp : SMComps)
				{
					FTransform Transform = SMComp->GetComponentTransform();

					if (Transform.GetScale3D().GetMin() < 0)
					{
						UE_LOG(IPELog, Warning, TEXT("Negative scale value in component:"));
						UE_LOG(IPELog, Warning, TEXT("%s -> %s -> %s -> (%s)"), *SMComp->GetOwner()->GetOuter()->GetOuter()->GetName(), *SMComp->GetOwner()->GetName(), *SMComp->GetName(), *Transform.GetScale3D().ToString());
					}

					Transform = Transform.GetRelativeTransform(IPTAActor->GetActorTransform());
					IPTAActor->IPOperationTransformsArray->PlacementTransforms.Add(Transform);
				}

				for (AActor* ActorToDestroy : OriginalActorsToDestroy)
				{
					if (AGroupActor* ActorGroup = Cast<AGroupActor>(ActorToDestroy->GroupActor))
					{
						ActorGroup->Remove(*ActorToDestroy);
					}

					ActorToDestroy->MarkPackageDirty();
					bool WasDestroyed = ActorToDestroy->GetWorld()->EditorDestroyActor(ActorToDestroy, false);
					checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ActorToDestroy->GetName(), *ActorToDestroy->GetActorLabel());
				}
			}
		}

		if (IPTAActors.Num() > 0)
		{
			for (AIPTransformsArrayActor* IPTAActor : IPTAActors)
			{
				IPTAActor->RunGeneration();
				GEditor->SelectActor(IPTAActor, true, false);
			}

			UE_LOG(IPELog, Warning, TEXT("%d StaticMeshComponents successfully converted to instances."), ProcessedSMComps.Num());
		}
	}
	else
	{
		UE_LOG(IPELog, Warning, TEXT("No StaticMeshComponents or valid StaticMesh properties found. Nothing to convert."));
		UE_LOG(IPELog, Warning, TEXT("Convertation aborted."));
	}
}

void UIPEFunctionLibrary::ConvertInstancesToStaticMeshes()
{
	USelection* Selection = GEditor->GetSelectedActors();
	TArray<UInstancedStaticMeshComponent*> ProcessedISMComps;
	TArray<AActor*> OriginalActorsToDestroy;

	for (FSelectionIterator Iter(*Selection); Iter; ++Iter)
	{
		if (AActor* SelectedActor = Cast<AActor>(*Iter))
		{
			TArray<UActorComponent*> AComponents;
			SelectedActor->GetComponents(UInstancedStaticMeshComponent::StaticClass(), AComponents);

			if (AComponents.Num() > 0)
			{
				for (UActorComponent* AComp : AComponents)
				{
					UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(AComp);

					if (ISMComp && ISMComp->GetStaticMesh() && ISMComp->GetInstanceCount() > 0)
					{
						ProcessedISMComps.Add(ISMComp);
					}
				}
			}
		}
	}

	if (ProcessedISMComps.Num() > 0)
	{
		GEditor->SelectNone(false, true);

		for (UInstancedStaticMeshComponent* ISMComp : ProcessedISMComps)
		{
			UStaticMesh* StaticMesh = ISMComp->GetStaticMesh();
			TArray<UMaterialInterface*> Materials;
			int32 NumMaterials = ISMComp->GetNumMaterials();

			for (int32 i = 0; i < NumMaterials; i++)
			{
				Materials.Add(ISMComp->GetMaterial(i));
			}

			FActorSpawnParameters SpawnInfo;
			SpawnInfo.OverrideLevel = ISMComp->GetOwner()->GetLevel();
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FName FolderName = *(FString(TEXT("Instanced_"))
				.Append(ISMComp->GetOwner()->GetName())
				.Append(FString(TEXT("_")))
				.Append(ISMComp->GetName()));

			for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
			{
				FTransform Transform;
				ISMComp->GetInstanceTransform(i, Transform);
				Transform *= ISMComp->GetComponentTransform();
				AActor* Actor = ISMComp->GetWorld()->SpawnActor(AStaticMeshActor::StaticClass(), &Transform, SpawnInfo);
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

			UE_LOG(IPELog, Warning, TEXT("%d instances successfully converted to static meshes!"), ISMComp->GetInstanceCount());

			OriginalActorsToDestroy.AddUnique(ISMComp->GetOwner());
		}

		for (AActor* ActorToDestroy : OriginalActorsToDestroy)
		{
			ActorToDestroy->MarkPackageDirty();
			bool WasDestroyed = ActorToDestroy->GetWorld()->EditorDestroyActor(ActorToDestroy, false);
			checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ActorToDestroy->GetName(), *ActorToDestroy->GetActorLabel());
		}
	}
	else
	{
		UE_LOG(IPELog, Warning, TEXT("No InstancedStaticMeshComponents, instances or valid StaticMesh properties found. Nothing to convert."));
		UE_LOG(IPELog, Warning, TEXT("Convertation aborted."));
	}
}

void UIPEFunctionLibrary::CheckNegativeScale()
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
									UE_LOG(IPELog, Warning, TEXT("Negative scale value in instance:"));
									UE_LOG(IPELog, Warning, TEXT("%s -> %s -> %s -> %d -> (%s)"), *SelectedActor->GetOuter()->GetOuter()->GetName(), *SelectedActor->GetName(), *ISMComp->GetName(), i, *InstanceTransf.GetScale3D().ToString());
								}
							}
						}
					}
					else if (UStaticMeshComponent* SMComp = Cast<UStaticMeshComponent>(AComp))
					{
						FVector CompScale = SMComp->GetComponentTransform().GetScale3D();
						if (CompScale.GetMin() < 0)
						{
							UE_LOG(IPELog, Warning, TEXT("Negative scale value in component:"));
							UE_LOG(IPELog, Warning, TEXT("%s -> %s -> %s -> (%s)"), *SelectedActor->GetOuter()->GetOuter()->GetName(), *SelectedActor->GetName(), *SMComp->GetName(), *CompScale.ToString());
						}
					}
				}
			}
		}
	}
}
// Convertation

// Math
FVector UIPEFunctionLibrary::GetLocationArrayAverageWithGridSnapping(const TArray<FVector>& Locations, float GridSize)
{
	FVector LocationSum(0, 0, 0);
	int32 LocationCount = 0;

	for (FVector L : Locations)
	{
		LocationSum += L;
		LocationCount++;
	}

	FVector Average(0, 0, 0);

	if (LocationCount > 0)
	{
		Average = LocationSum / ((float)LocationCount);
	}

	Average.X = FMath::FloorToInt(Average.X / GridSize) * GridSize;
	Average.Y = FMath::FloorToInt(Average.Y / GridSize) * GridSize;
	Average.Z = FMath::FloorToInt(Average.Z / GridSize) * GridSize;

	return Average;
}
// Math
#endif
