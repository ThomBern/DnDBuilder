// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Grid.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"


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
	gridTileSize = FVector(200.f, 200.f, 0.f);
	gridTileCount = FVector2D(10.f, 10.f);
	gridShape = EDDB_Gridshape::SQUARE;
	gridBottomLeftLocation = gridCenterLocation - FVector((gridTileCount / 2) * FVector2D(gridTileSize.X, gridTileSize.Y), 0.f);

}

// Called when the game starts or when spawned
void ADDB_Grid::BeginPlay()
{
	Super::BeginPlay();
}

void ADDB_Grid::SpawnGrid(FVector centerLocation, FVector tileSize, FVector2D tileCount, EDDB_Gridshape shape)
{
	gridCenterLocation = centerLocation;
	gridTileSize = tileSize;
	gridTileCount.Set(tileCount.X, tileCount.Y);
	gridShape = shape;
	gridBottomLeftLocation = gridCenterLocation - FVector((gridTileCount / 2) * FVector2D(gridTileSize.X, gridTileSize.Y), 0.f);
	
	DestroyGrid();

	FDDB_Gridshape_Data* row = GetCurrentShapeData();

	if (!row) {
		UE_LOG(LogTemp, Warning, TEXT("Row not found; returning from SpawnGrid method"));		
		return;
	}

	InstancedMesh->SetStaticMesh(row->flatMesh);
	InstancedMesh->SetMaterial(0, row->flatBorderMaterial);

	for (uint32 x = 0; x < FMath::RoundFromZero(gridTileCount.X); x++) {
		for (uint32 y = 0; y < FMath::RoundFromZero(gridTileCount.Y); y++) {
			FTransform tileTransform;
			tileTransform.SetScale3D(gridTileSize / row->meshSize);
			tileTransform.SetTranslation(gridBottomLeftLocation + FVector(gridTileSize.X * x, gridTileSize.Y * y, 0.f));
		
			InstancedMesh->AddInstance(tileTransform);
		}
	}

}

void ADDB_Grid::DestroyGrid()
{
	InstancedMesh->ClearInstances();
}

FDDB_Gridshape_Data* ADDB_Grid::GetCurrentShapeData()
{
	FText rowName;
	UEnum::GetDisplayValueAsText(gridShape, rowName);

	FDDB_Gridshape_Data* row = nullptr;
	row = gridDT->FindRow<FDDB_Gridshape_Data>(FName(rowName.ToString()), "");

    return row;
}

// Called every frame
void ADDB_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_Grid::OnConstruction(const FTransform &Transform)
{
	SpawnGrid(gridCenterLocation, gridTileSize, gridTileCount, gridShape);
}
