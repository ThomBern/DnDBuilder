// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DDB_FL_Utilities.generated.h"

/**
 * 
 */
UCLASS()
class DNDBUILDER_API UDDB_FL_Utilities : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure)
	static FVector SnapVectorToVector(FVector v1, FVector v2);
	
	UFUNCTION(BlueprintPure)
	static bool IsFloatEven(float f);

	UFUNCTION(BlueprintPure)
	static bool IsIntEven(int i);
};
