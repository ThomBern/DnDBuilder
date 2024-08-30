// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_ShowTileNeighbors.h"

#include "../../../Grid/DDB_GridPathfinding.h"
#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_ShowTileNeighbors::ExecuteAction(FIntPoint index)
{
    ADDB_Grid* grid = playerActions->grid;

    grid->ClearStateFromTiles(EDDB_TileState::NEIGHBOR);

    TArray<FIntPoint> neighbors = grid->gridPathfinding->GetValidTileNeighbors(index, bIncludeDiagonals);

    for (const FIntPoint& neighbor : neighbors) {
        grid->AddStateToTile(neighbor, EDDB_TileState::NEIGHBOR);
    }


}
