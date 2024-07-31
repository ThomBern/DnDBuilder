// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_FL_Tile.h"
#include "UObject/ConstructorHelpers.h"

UDDB_FL_Tile::UDDB_FL_Tile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UDDB_FL_Tile::IsTileTypeWalkable(EDDB_TileType type)
{
    return type != EDDB_TileType::NONE && type != EDDB_TileType::OBSTACLE;
}
