// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include"DDB_TileType.generated.h"

UENUM(BlueprintType)
enum class EDDB_TileType: uint8
{
	NONE UMETA(DisplayName="None"),
	NORMAL UMETA(DisplayName="Normal"),
	OBSTACLE UMETA(DisplayName="Obstacle"),
	NUM_MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct DNDBUILDER_API FDDB_Tile_Data: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDDB_TileType type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform transform;

	FDDB_Tile_Data() {	}
	FDDB_Tile_Data(FIntPoint inIndex, EDDB_TileType inType, FTransform inTransform)
	{
		index = inIndex;
		type = inType;
		transform = inTransform;
	}
};
