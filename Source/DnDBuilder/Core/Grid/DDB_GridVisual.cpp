// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_GridVisual.h"

#include "Components/ChildActorComponent.h"

#include "DDB_Grid.h"
#include "DDB_GridMeshInstance.h"
#include "DDB_Gridshape_Data.h"
#include "DDB_TileType.h"

#include "DDB_FL_Tile.h"

// Sets default values
ADDB_GridVisual::ADDB_GridVisual()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CA_GridMeshInstance = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_GridMeshInstance"));
	CA_GridMeshInstance->SetupAttachment(RootComponent);

	offsetFromGround = 2.f;
}

// Called when the game starts or when spawned
void ADDB_GridVisual::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADDB_GridVisual::SetOffsetFromGround(float offset)
{
	offsetFromGround = offset;

	FVector newLocation = GetActorLocation();
	newLocation.Z = offsetFromGround;

	SetActorLocation(newLocation);
}

// Called every frame
void ADDB_GridVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_GridVisual::OnConstruction(const FTransform &Transform)
{
	CA_GridMeshInstance->SetChildActorClass(ADDB_GridMeshInstance::StaticClass());
}

void ADDB_GridVisual::InitializeGridVisual(ADDB_Grid* inGrid)
{
	grid = inGrid;
	gridMeshInstance = Cast<ADDB_GridMeshInstance>(CA_GridMeshInstance->GetChildActor());

	FDDB_Gridshape_Data shapeData = grid->GetCurrentShapeData();

	gridMeshInstance->InitializeGridMeshInstance(shapeData.flatMesh, shapeData.flatBorderMaterial, FVector(0.f,0.f,0.f), ECollisionEnabled::QueryOnly);

	SetActorLocation(FVector(0.f,0.f,0.f));

	SetOffsetFromGround(offsetFromGround);
}

void ADDB_GridVisual::UpdateTileVisual(FDDB_Tile_Data data)
{
	gridMeshInstance->RemoveInstance(data.index);

	if (UDDB_FL_Tile::IsTileTypeWalkable(data.type)) {
		gridMeshInstance->AddInstance(data.transform, data.index);
	}
}

void ADDB_GridVisual::DestroyGridVisual()
{
	if (gridMeshInstance)
		gridMeshInstance->ClearInstances();
}
