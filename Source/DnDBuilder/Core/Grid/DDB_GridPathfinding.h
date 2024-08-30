// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DDB_GridPathfinding.generated.h"

class ADDB_Grid;

UCLASS()
class DNDBUILDER_API ADDB_GridPathfinding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_GridPathfinding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeGridPathfinding(ADDB_Grid* inGrid);

	UFUNCTION(BlueprintCallable)
	TArray<FIntPoint> GetValidTileNeighbors(FIntPoint index, bool includeDiagonals);
	TArray<FIntPoint> GetNeighborIndexes(FIntPoint index, bool includeDiagonals);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	TArray<FIntPoint> GetValidTileNeighborsSquare(FIntPoint index, bool includeDiagonals) const;
	TArray<FIntPoint> GetValidTileNeighborsHexagon(FIntPoint index) const;

	TObjectPtr<ADDB_Grid> grid;

};
