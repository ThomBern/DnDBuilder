// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_GridPathfinding.h"

#include "Math/UnrealMathUtility.h"

#include "DDB_Grid.h"

// Sets default values
ADDB_GridPathfinding::ADDB_GridPathfinding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADDB_GridPathfinding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDB_GridPathfinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_GridPathfinding::InitializeGridPathfinding(ADDB_Grid* inGrid)
{
	grid = inGrid;
}

TArray<FIntPoint> ADDB_GridPathfinding::GetValidTileNeighbors(FIntPoint index, bool includeDiagonals)
{
	TArray<FIntPoint> neighbors = GetNeighborIndexes(index, includeDiagonals);

	FDDB_Tile_Data* inputData = grid->gridTiles.Find(index);

	TArray<FIntPoint> validNeighbors;

	for (const FIntPoint& neighbor : neighbors) {
		FDDB_Tile_Data* data = grid->gridTiles.Find(neighbor);

		if (!UDDB_FL_Tile::IsTileTypeWalkable(data->type)) continue;
		
		float heightDiff = FMath::Abs(data->transform.GetLocation().Z - inputData->transform.GetLocation().Z);

		if (heightDiff > grid->gridTileSize.Z) continue;

		validNeighbors.Add(neighbor);
	}

	return validNeighbors;
}

TArray<FIntPoint> ADDB_GridPathfinding::GetNeighborIndexes(FIntPoint index, bool includeDiagonals)
{
	switch(grid->gridShape) {
		case EDDB_Gridshape::SQUARE:
			return GetValidTileNeighborsSquare(index, includeDiagonals);
		case EDDB_Gridshape::HEXAGON:
			return GetValidTileNeighborsHexagon(index);
		default:
			return TArray<FIntPoint>();
	}
}


TArray<FIntPoint> ADDB_GridPathfinding::GetValidTileNeighborsSquare(FIntPoint index, bool includeDiagonals) const
{
	TArray<FIntPoint> neighbors;

	neighbors.Add(index + FIntPoint(1,0));
	neighbors.Add(index + FIntPoint(0,1));
	neighbors.Add(index + FIntPoint(-1,0));
	neighbors.Add(index + FIntPoint(0,-1));

	if (includeDiagonals) {
		neighbors.Add(index + FIntPoint(1,1));
		neighbors.Add(index + FIntPoint(-1,1));
		neighbors.Add(index + FIntPoint(-1,-1));
		neighbors.Add(index + FIntPoint(1,-1));
	}

	return neighbors;
}

TArray<FIntPoint> ADDB_GridPathfinding::GetValidTileNeighborsHexagon(FIntPoint index) const
{
	TArray<FIntPoint> neighbors;

	neighbors.Add(index + FIntPoint(1,1));
	neighbors.Add(index + FIntPoint(0,2));
	neighbors.Add(index + FIntPoint(-1,1));
	neighbors.Add(index + FIntPoint(-1,-1));
	neighbors.Add(index + FIntPoint(0,-2));
	neighbors.Add(index + FIntPoint(1,-1));

    return neighbors;
}
