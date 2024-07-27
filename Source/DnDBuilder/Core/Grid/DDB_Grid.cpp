// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Grid.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetSystemLibrary.h"

#include "../Utilities/DDB_FL_Utilities.h"

// Sets default values
ADDB_Grid::ADDB_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	InstancedMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UDataTable> 
		gridShapeRef(TEXT("DataTable'/Game/Blueprint/Core/DDB_DT_Gridshape_Data.DDB_DT_Gridshape_Data'"));

	if (!gridShapeRef.Object) {
		UE_LOG(LogTemp, Warning, TEXT("Gridshape DT not found; returning from SpawnGrid method"));		

		return;
	}

	gridDT = gridShapeRef.Object;

	gridCenterLocation = FVector(0.f, 0.f, 0.f);
	gridTileSize = FVector(200.f, 200.f, 50.f);
	gridTileCount = FIntPoint(10, 10);
	gridShape = EDDB_Gridshape::SQUARE;
	gridBottomLeftLocation = gridCenterLocation - FVector((FVector2D(gridTileCount) / 2) * FVector2D(gridTileSize.X, gridTileSize.Y), 0.f);
	gridOffsetFromGround = 2.f;
}

// Called every frame
void ADDB_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_Grid::OnConstruction(const FTransform &Transform)
{
	// SpawnGrid(GetActorLocation(), gridTileSize, gridTileCount, gridShape);
}

// Called when the game starts or when spawned
void ADDB_Grid::BeginPlay()
{
	Super::BeginPlay();
}

void ADDB_Grid::SpawnGrid(FVector centerLocation, FVector tileSize, FIntPoint tileCount, EDDB_Gridshape shape, bool useEnvironment)
{
	gridCenterLocation = centerLocation;
	gridTileSize = tileSize;
	gridTileCount = tileCount;
	gridShape = shape;

	SetGridOffsetFromGround(gridOffsetFromGround);

	FVector center, bottomLeft;
	CalculateCenterAndBottomLeft(center, bottomLeft);
	gridCenterLocation = center;
	gridBottomLeftLocation = bottomLeft;

	DestroyGrid();

	FDDB_Gridshape_Data* row = GetCurrentShapeData();

	if (!row) {
		UE_LOG(LogTemp, Warning, TEXT("Row not found; returning from SpawnGrid method"));		
		return;
	}

	auto LoopBody = [&](int x, int y) -> void {
		FTransform tileTransform;
		tileTransform.SetScale3D(gridTileSize / row->meshSize);
		tileTransform.SetTranslation(GetTileLocationFromGridIndex(FIntPoint(x,y)));
		
		if (useEnvironment) {
			bool hit = false;
			FVector outLocation;
			TraceForGround(tileTransform.GetTranslation(), hit, outLocation);

			if(hit) {
				UE_LOG(LogTemp, Warning, TEXT("in if"));		
				tileTransform.SetTranslation(outLocation);
				InstancedMesh->AddInstance(tileTransform, false);
			}
		}
		else {
			InstancedMesh->AddInstance(tileTransform, false);
		}
	};

	InstancedMesh->SetStaticMesh(row->flatMesh);
	InstancedMesh->SetMaterial(0, row->flatBorderMaterial);

	for (int32 x = 0; x < gridTileCount.X; x++) {
		if (gridShape != EDDB_Gridshape::HEXAGON) {
			for (int32 y = 0; y < gridTileCount.Y; y++) {
				LoopBody(x,y);
			}
		}
		else { // HEXAGON
			int firstIndex = UDDB_FL_Utilities::IsIntEven(x) ? 0 : 1;
			for (int32 y = firstIndex; y < gridTileCount.Y * 2; y++) {
				LoopBody(x,y);
				y++;
			}
		}
	}

}

void ADDB_Grid::DestroyGrid()
{
	InstancedMesh->ClearInstances();
}

void ADDB_Grid::TraceForGround(FVector location, bool& hitSomething, FVector& outLocation)
{
	FVector start = location + FVector(0.f,0.f,1000.f);
	FVector end = location - FVector(0.f,0.f,1000.f);

	float radius = gridTileSize.X / 3;

	FCollisionShape sphere = FCollisionShape::MakeSphere(radius);
	TArray<FHitResult> outHits;
	FCollisionQueryParams params(FName(TEXT("TraceForGround")), false, this);

	// check if not correct, just use outHits length instead
	GetWorld()->SweepMultiByChannel(
		outHits,
		start,
		end,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		sphere,
		params
	);

	if (!outHits.IsEmpty()) {
		FVector firstHitLocation = outHits[0].Location;
		
		outLocation = FVector(location.X, location.Y, FMath::GridSnap(firstHitLocation.Z - radius, gridTileSize.Z));
		hitSomething = true;
	}

}

void ADDB_Grid::SetGridOffsetFromGround(float offset)
{
	InstancedMesh->SetWorldLocation(FVector(0.f,0.f,offset));
}

FDDB_Gridshape_Data* ADDB_Grid::GetCurrentShapeData() const
{
	FText rowName;
	UEnum::GetDisplayValueAsText(gridShape, rowName);

	FDDB_Gridshape_Data* row = nullptr;
	row = gridDT->FindRow<FDDB_Gridshape_Data>(FName(rowName.ToString()), "");

    return row;
}

void ADDB_Grid::CalculateCenterAndBottomLeft(FVector& center, FVector& bottomLeft)
{

	if (gridShape == EDDB_Gridshape::SQUARE) {
		center = UDDB_FL_Utilities::SnapVectorToVector(gridCenterLocation, gridTileSize);

		FVector2D tileCount = FVector2D(gridTileCount);
		if (!UDDB_FL_Utilities::IsIntEven(gridTileCount.X)) {
			tileCount.X = gridTileCount.X - 1.f;
		}
		if (!UDDB_FL_Utilities::IsIntEven(gridTileCount.Y)) {
			tileCount.Y = gridTileCount.Y - 1.f;
		}

		bottomLeft = center - FVector((tileCount / 2) * FVector2D(gridTileSize.X, gridTileSize.Y), 0.f);
	}

	if (gridShape == EDDB_Gridshape::HEXAGON) {
		center = UDDB_FL_Utilities::SnapVectorToVector(gridCenterLocation, gridTileSize * FVector(1.5f,1.f,1.f));
		
		FVector distance = FVector((FVector2D(gridTileCount) / FVector2D(3.f,2.f)) * FVector2D(gridTileSize.X, gridTileSize.Y), 0.f);

		bottomLeft = center - UDDB_FL_Utilities::SnapVectorToVector(distance, gridTileSize * FVector(1.5f,1.f,1.f));
	}
}

FVector ADDB_Grid::GetTileLocationFromGridIndex(FIntPoint gridIndex) const
{
	FVector2D fittedIndex = FVector2D(gridIndex);

	if (gridShape == EDDB_Gridshape::HEXAGON) {
		fittedIndex.X = gridIndex.X * 0.75f;
		fittedIndex.Y = gridIndex.Y * 0.5f;
	}

	FVector tileLocation = gridBottomLeftLocation + FVector(gridTileSize.X * fittedIndex.X, gridTileSize.Y * fittedIndex.Y, 0.f);

    return tileLocation;
}
