// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDDB_TileType: uint8
{
	NONE UMETA(DisplayName="None"),
	NORMAL UMETA(DisplayName="Normal"),
	OBSTACLE UMETA(DisplayName="Obstacle"),
	NUM_MAX UMETA(Hidden)
};