// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DDB_Gridshape_Data.h"
#include "DDB_TileType.h"

#include "DDB_Grid.generated.h"

class UInstancedStaticMeshComponent;
class UChildActorComponent;
class ADDB_GridVisual;
struct FDDB_TileData;

UCLASS()
class DNDBUILDER_API ADDB_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_Grid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	FDDB_Gridshape_Data GetCurrentShapeData() const;

	UFUNCTION(BlueprintCallable)
	void SpawnGrid(FVector centerLocation, FVector tileSize, FIntPoint tileCount, EDDB_Gridshape shape, bool useEnvironment = false);
	
	UFUNCTION(BlueprintCallable)
	void DestroyGrid();

	UFUNCTION(BlueprintCallable)
	void TraceForGround(FVector location, EDDB_TileType& tileType, FVector& outLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FVector gridCenterLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
	FVector gridBottomLeftLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FVector gridTileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FIntPoint gridTileCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EDDB_Gridshape gridShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ADDB_GridVisual> gridVisual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FIntPoint, FDDB_Tile_Data> gridTiles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	void CalculateCenterAndBottomLeft(FVector& center, FVector& bottomLeft);
	
	FVector GetTileLocationFromGridIndex(FIntPoint gridIndex) const;

	void AddGridTile(FDDB_Tile_Data data);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> CA_GridVisual;

};
