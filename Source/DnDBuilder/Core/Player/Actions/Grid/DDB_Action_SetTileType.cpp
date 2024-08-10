// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_SetTileType.h"

#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_SetTileType::ExecuteAction(FIntPoint index)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName());

    ADDB_Grid* grid = playerActions->grid;
    if (grid->IsIndexValid(index)) {
        FDDB_Tile_Data* data = grid->gridTiles.Find(index);
        data->type = tileType;
        
        grid->AddGridTile(*data);
    }
}