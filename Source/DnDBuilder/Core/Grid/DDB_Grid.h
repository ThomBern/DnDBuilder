// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DDB_Gridshape_Data.h"

#include "DDB_Grid.generated.h"

class UInstancedStaticMeshComponent;
class UDataTable;

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

	UFUNCTION(BlueprintCallable)
	void SpawnGrid(FVector centerLocation, FVector tileSize, FVector2D tileCount, EDDB_Gridshape shape);
	
	UFUNCTION(BlueprintCallable)
	void DestroyGrid();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid vars")
	FVector gridCenterLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid vars")
	FVector gridBottomLeftLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid vars")
	FVector gridTileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid vars")
	FVector2D gridTileCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid vars")
	EDDB_Gridshape gridShape;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	FDDB_Gridshape_Data* GetCurrentShapeData() const;
	void CalculateCenterAndBottomLeft(FVector& center, FVector& bottomLeft);
	FVector GetTileLocationFromGridIndex(FVector2D gridIndex) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInstancedStaticMeshComponent> InstancedMesh;

	TObjectPtr<UDataTable> gridDT;
};
