// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include"DDB_Gridshape_Data.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DNDBUILDER_API FDDB_Gridshape_Data: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector meshSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* meshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* flatMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* flatBorderMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* flatFilledMaterial;

	FDDB_Gridshape_Data()
	{
		meshSize = FVector(100.f, 100.f, 100.f);
	}
};

UENUM(BlueprintType)
enum class EDDB_Gridshape: uint8
{
	NONE UMETA(DisplayName="None"),
	SQUARE UMETA(DisplayName="Square"),
	HEXAGON UMETA(DisplayName="Hexagon"),
	NUM_MAX UMETA(Hidden)
};
