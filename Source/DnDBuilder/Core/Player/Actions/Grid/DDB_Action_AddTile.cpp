// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_AddTile.h"

#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_AddTile::ExecuteAction(FIntPoint index)
{
    ADDB_Grid* grid = playerActions->grid;
    if (!grid->IsIndexValid(index)) {
        EDDB_TileType type;
        FVector outLocation;

        grid->TraceForGround(grid->GetTileLocationFromGridIndex(index), type, outLocation);
        
        FTransform transform;
        
        transform.SetLocation(outLocation);
        transform.SetScale3D(grid->GetTileScale());

        FDDB_Tile_Data tileData(index, EDDB_TileType::NORMAL, transform);

        grid->AddGridTile(tileData);
    }
}
