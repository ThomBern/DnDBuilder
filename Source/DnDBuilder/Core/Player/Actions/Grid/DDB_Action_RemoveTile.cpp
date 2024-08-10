// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action_RemoveTile.h"

#include "../../../Grid/Utilities/DDB_FL_Tile.h"

void ADDB_Action_RemoveTile::ExecuteAction(FIntPoint index)
{
    playerActions->grid->RemoveGridTile(index);
}
