// Dmitriy Barannik aka redbox, 2020

#include "Objects/IPEFunctionLibrary.h"
#include "Engine/Selection.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Actors/IPTransformsArrayActor.h"

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
				//FTransform SpawnTransform = this->GetActorTransform();
				FTransform SpawnTransform = FTransform();
				AActor* Actor = Level->GetWorld()->SpawnActor(AIPTransformsArrayActor::StaticClass(), &SpawnTransform, SpawnInfo);
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
							UE_LOG(LogTemp, Warning, TEXT("Negative scale value in component:"));
							UE_LOG(LogTemp, Warning, TEXT("%s -> %s -> %s -> (%s)"), *SMComp->GetOwner()->GetOuter()->GetOuter()->GetName(), *SMComp->GetOwner()->GetName(), *SMComp->GetName(), *Transform.GetScale3D().ToString());
						}

						Transform = Transform.GetRelativeTransform(IPTAActor->GetActorTransform());
						IPTAActor->IPProcedureTransformsArray->PlacementTransforms.Add(Transform);

						//if (bRemoveOriginal)
						//{
							OriginalActorsToDestroy.AddUnique(SMComp->GetOwner());
						//}
					}
				}

				//if (bRemoveOriginal)
				//{
					for (AActor* ActorToDestroy : OriginalActorsToDestroy)
					{
						ActorToDestroy->MarkPackageDirty();
						bool WasDestroyed = ActorToDestroy->GetWorld()->EditorDestroyActor(ActorToDestroy, false);
						checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ActorToDestroy->GetName(), *ActorToDestroy->GetActorLabel());
					}
				//}
			}
		}

		if (IPTAActors.Num() > 0)
		{
			for (AIPTransformsArrayActor* IPTAActor : IPTAActors)
			{
				IPTAActor->RunGeneration();
				GEditor->SelectActor(IPTAActor, true, false);
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

			UE_LOG(LogTemp, Warning, TEXT("%d instances successfully converted to static meshes!"), ISMComp->GetInstanceCount());

			//if (bRemoveOriginal)
			//{
				OriginalActorsToDestroy.AddUnique(ISMComp->GetOwner());
			//}
		}

		//if (bRemoveOriginal)
		//{
			for (AActor* ActorToDestroy : OriginalActorsToDestroy)
			{
				ActorToDestroy->MarkPackageDirty();
				bool WasDestroyed = ActorToDestroy->GetWorld()->EditorDestroyActor(ActorToDestroy, false);
				checkf(WasDestroyed, TEXT("Failed to destroy Actor %s (%s)"), *ActorToDestroy->GetName(), *ActorToDestroy->GetActorLabel());
			}
		//}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No InstancedStaticMeshComponents, instances or valid StaticMesh properties found. Nothing to convert."));
		UE_LOG(LogTemp, Warning, TEXT("Convertation aborted."));
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
									UE_LOG(LogTemp, Warning, TEXT("Negative scale value in instance:"));
									UE_LOG(LogTemp, Warning, TEXT("%s -> %s -> %s -> %d -> (%s)"), *SelectedActor->GetOuter()->GetOuter()->GetName(), *SelectedActor->GetName(), *ISMComp->GetName(), i, *InstanceTransf.GetScale3D().ToString());
								}
							}
						}
					}
					else if (UStaticMeshComponent* SMComp = Cast<UStaticMeshComponent>(AComp))
					{
						FVector CompScale = SMComp->GetComponentTransform().GetScale3D();
						if (CompScale.GetMin() < 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("Negative scale value in component:"));
							UE_LOG(LogTemp, Warning, TEXT("%s -> %s -> %s -> (%s)"), *SelectedActor->GetOuter()->GetOuter()->GetName(), *SelectedActor->GetName(), *SMComp->GetName(), *CompScale.ToString());
						}
					}
				}
			}
		}
	}
}
// Convertation
#endif