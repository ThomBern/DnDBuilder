// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DDB_GridVisual.generated.h"

class UChildActorComponent;
class ADDB_Grid;
class ADDB_GridMeshInstance;
struct FDDB_Tile_Data;

UCLASS()
class DNDBUILDER_API ADDB_GridVisual : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_GridVisual();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void InitializeGridVisual(ADDB_Grid* inGrid);

	UFUNCTION(BlueprintCallable)
	void UpdateTileVisual(FDDB_Tile_Data data);

	UFUNCTION(BlueprintCallable)
	void DestroyGridVisual();

	UFUNCTION(BlueprintCallable)
	void SetOffsetFromGround(float offset);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float offsetFromGround;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> CA_GridMeshInstance;

	TObjectPtr<ADDB_Grid> grid;
	TObjectPtr<ADDB_GridMeshInstance> gridMeshInstance;
};
