// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_SelectTile.h"

#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_SelectTile::ExecuteAction(FIntPoint index)
{
    ADDB_Grid* grid = playerActions->grid;
    if (playerActions->selectedTile != index) {
        grid->RemoveStateFromTile(playerActions->selectedTile, EDDB_TileState::SELECTED);
        
        playerActions->selectedTile = index;
        grid->AddStateToTile(playerActions->selectedTile, EDDB_TileState::SELECTED);
    }
    else {
        grid->RemoveStateFromTile(playerActions->selectedTile, EDDB_TileState::SELECTED);
        playerActions->selectedTile = FIntPoint(-999, -999); // invalid index 
    }
}

void ADDB_Action_SelectTile::Destroyed()
{
    ExecuteAction(FIntPoint(-999,-999));

    Super::Destroyed();
}