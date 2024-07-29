// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DDB_FL_Gridshape.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class DNDBUILDER_API UDDB_FL_Gridshape : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure)
	static bool GetShapeData(EDDB_Gridshape gridShape, FDDB_Gridshape_Data& outRow);
	
	static TObjectPtr<UDataTable> gridDT;
};
