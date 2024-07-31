// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DDB_FL_Tile.generated.h"


/**
 * 
 */
UCLASS()
class DNDBUILDER_API UDDB_FL_Tile : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintPure)
	static bool IsTileTypeWalkable(EDDB_TileType type);
};
