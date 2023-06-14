// redbox, 2023

#include "Actors/IPSplineProceduralMeshActor.h"
#include "InstancedPlugin.h"
#include "Components/SplineComponent.h"
#include "GeomTools.h"

AIPSplineProceduralMeshActor::AIPSplineProceduralMeshActor()
{
#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;
	SplineComponent->SetClosedLoop(true, true);

	bLinearSpline = false;
	bFromSplinePoints = true;
	SplineSubdivisions = 0;
	bFlipNormal = false;
	bCreateCollision = false;
#endif

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(RootComponent);
	ProceduralMeshComponent->Mobility = EComponentMobility::Static;
}

void AIPSplineProceduralMeshActor::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	SplineComponent->SetClosedLoop(true, true);

	RunGeneration();
#endif
}

#if WITH_EDITOR
void AIPSplineProceduralMeshActor::RunGeneration()
{
	Super::RunGeneration();

	ProceduralMeshComponent->ClearAllMeshSections();

	const int32 NumberOfSplinePoints = SplineComponent->GetNumberOfSplinePoints();
	if (bLinearSpline)
	{
		for (int32 i = 0; i < NumberOfSplinePoints; i++)
		{
			SplineComponent->SetSplinePointType(i, ESplinePointType::Linear, true);
		}
	}

	// Vertices
	TArray<FProcMeshVertex> PolyVertices;
	if (bFromSplinePoints)
	{
		const int32 NumberOfVertices = NumberOfSplinePoints;
		for (int32 i = 0; i < NumberOfVertices; i++)
		{
			const FVector PointLocation = SplineComponent->GetLocationAtDistanceAlongSpline(SplineComponent->GetDistanceAlongSplineAtSplinePoint(i), ESplineCoordinateSpace::Local);
			FProcMeshVertex Vertex = FProcMeshVertex();
			Vertex.Position = PointLocation;
			PolyVertices.Add(Vertex);
		}
	}
	else
	{
		const float SplineLength = SplineComponent->GetSplineLength();
		const int32 NumberOfVertices = NumberOfSplinePoints * (SplineSubdivisions == 0 ? 1 : SplineSubdivisions + 1);
		for (int32 i = 0; i < NumberOfVertices; i++)
		{
			const FVector PointLocation = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * i / NumberOfVertices, ESplineCoordinateSpace::Local);
			FProcMeshVertex Vertex = FProcMeshVertex();
			Vertex.Position = PointLocation;
			PolyVertices.Add(Vertex);
		}
	}

	// UVs
	float MinX = MAX_flt;
	float MinY = MAX_flt;
	float MaxX = MIN_flt;
	float MaxY = MIN_flt;

	for (int32 i = 0; i < PolyVertices.Num(); i++)
	{
		MinX = FMath::Min(MinX, PolyVertices[i].Position.X);
		MinY = FMath::Min(MinY, PolyVertices[i].Position.Y);
		MaxX = FMath::Max(MaxX, PolyVertices[i].Position.X);
		MaxY = FMath::Max(MaxY, PolyVertices[i].Position.Y);
	}

	const float RatioX = FMath::Abs(MaxX - MinX);
	const float RatioY = FMath::Abs(MaxY - MinY);
	const float RatioMax = FMath::Max(RatioX, RatioY);

	for (int32 i = 0; i < PolyVertices.Num(); i++)
	{
		FVector2D UV0((PolyVertices[i].Position.X - MinX) / RatioMax, (PolyVertices[i].Position.Y - MinY) / RatioMax);
		PolyVertices[i].UV0 = UV0;
	}

	// Triangles
	TArray<int32> Triangles;
	if (!TriangulatePoly(Triangles, const_cast<const TArray<FProcMeshVertex>&>(PolyVertices), FVector3f(0.f, 0.f, 1.f)))
	{
		UE_LOG(LogIP, Warning, TEXT("Failed to triangulate poly!"));
	}

	// Mesh section
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	for (int32 i = 0; i < PolyVertices.Num(); i++)
	{
		Vertices.Add(PolyVertices[i].Position);
		Normals.Add(PolyVertices[i].Normal);
		UV0.Add(PolyVertices[i].UV0);
		VertexColors.Add(PolyVertices[i].Color);
		Tangents.Add(PolyVertices[i].Tangent);
	}

	ProceduralMeshComponent->CreateMeshSection(0,
		const_cast<const TArray<FVector>&>(Vertices),
		const_cast<const TArray<int32>&>(Triangles),
		const_cast<const TArray<FVector>&>(Normals),
		const_cast<const TArray<FVector2D>&>(UV0),
		const_cast<const TArray<FColor>&>(VertexColors),
		const_cast<const TArray<FProcMeshTangent>&>(Tangents),
		bCreateCollision);
}

bool AIPSplineProceduralMeshActor::TriangulatePoly(TArray<int32>& OutTris, const TArray<FProcMeshVertex>& PolyVerts, const FVector3f& PolyNormal)
{
	int32 NumVerts = PolyVerts.Num();
	if (NumVerts < 3)
	{
		return false;
	}
	else if (NumVerts == 3)
	{
		OutTris.Add(0);
		OutTris.Add(2);
		OutTris.Add(1);

		return true;
	}

	// Init array of vert indices, in order. We'll modify this
	TArray<int32> VertIndices;
	VertIndices.AddUninitialized(NumVerts);
	for (int VertIndex = 0; VertIndex < NumVerts; VertIndex++)
	{
		VertIndices[VertIndex] = VertIndex;
	}

	// Keep iterating while there are still vertices
	while (VertIndices.Num() >= 3)
	{
		// Look for an 'ear' triangle
		bool bFoundEar = false;
		for (int32 EarVertexIndex = 0; EarVertexIndex < VertIndices.Num(); EarVertexIndex++)
		{
			// Triangle is 'this' vert plus the one before and after it
			const int32 AIndex = (EarVertexIndex == 0) ? VertIndices.Num() - 1 : EarVertexIndex - 1;
			const int32 BIndex = EarVertexIndex;
			const int32 CIndex = (EarVertexIndex + 1) % VertIndices.Num();

			const FProcMeshVertex& AVert = PolyVerts[VertIndices[AIndex]];
			const FProcMeshVertex& BVert = PolyVerts[VertIndices[BIndex]];
			const FProcMeshVertex& CVert = PolyVerts[VertIndices[CIndex]];

			// Check that this vertex is convex (cross product must be positive)
			const FVector3f ABEdge = FVector3f(BVert.Position - AVert.Position);
			const FVector3f ACEdge = FVector3f(CVert.Position - AVert.Position);
			const float TriangleDeterminant = (ABEdge ^ ACEdge) | PolyNormal;
			if (TriangleDeterminant > 0.f)
			{
				continue;
			}

			bool bFoundVertInside = false;
			// Look through all verts before this in array to see if any are inside triangle
			for (int32 VertexIndex = 0; VertexIndex < VertIndices.Num(); VertexIndex++)
			{
				const FProcMeshVertex& TestVert = PolyVerts[VertIndices[VertexIndex]];

				if (VertexIndex != AIndex &&
					VertexIndex != BIndex &&
					VertexIndex != CIndex &&
					FGeomTools::PointInTriangle((FVector3f)AVert.Position, (FVector3f)BVert.Position, (FVector3f)CVert.Position, (FVector3f)TestVert.Position))
				{
					bFoundVertInside = true;
					break;
				}
			}

			// Triangle with no verts inside - its an 'ear'! 
			if (!bFoundVertInside)
			{
				if (!bFlipNormal)
				{
					OutTris.Add(VertIndices[AIndex]);
					OutTris.Add(VertIndices[CIndex]);
					OutTris.Add(VertIndices[BIndex]);
				}
				else
				{
					OutTris.Add(VertIndices[AIndex]);
					OutTris.Add(VertIndices[BIndex]);
					OutTris.Add(VertIndices[CIndex]);
				}

				// And remove vertex from polygon
				VertIndices.RemoveAt(EarVertexIndex);

				bFoundEar = true;
				break;
			}
		}

		// If we couldn't find an 'ear' it indicates something is bad with this polygon - discard triangles and return.
		if (!bFoundEar)
		{
			return false;
		}
	}

	return true;
}
#endif