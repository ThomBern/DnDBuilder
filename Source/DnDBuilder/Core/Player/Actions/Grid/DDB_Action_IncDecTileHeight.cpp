// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_IncDecTileHeight.h"

#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_IncDecTileHeight::ExecuteAction(FIntPoint index)
{
    ADDB_Grid* grid = playerActions->grid;
    if (grid->IsIndexValid(index)) {
        FDDB_Tile_Data* data = grid->gridTiles.Find(index);
        
        FVector newHeight = data->transform.GetLocation();

        if (increase) {
            newHeight.Z += grid->gridTileSize.Z;
        }
        else {
            newHeight.Z -= grid->gridTileSize.Z;
        }

        data->transform.SetLocation(newHeight);
        
        grid->AddGridTile(*data);
    }
}
