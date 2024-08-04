// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Utilities/DDB_FL_Tile.h"

#include "DDB_GridMeshInstance.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class DNDBUILDER_API ADDB_GridMeshInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_GridMeshInstance();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddInstance(FTransform transform, FIntPoint index, TArray<EDDB_TileState> states);
	void RemoveInstance(FIntPoint index);
	void ClearInstances();

	// UFUNCTION(BlueprintCallable)
	void InitializeGridMeshInstance(UStaticMesh* mesh, UMaterialInstance* material, FVector color, ECollisionEnabled::Type collision);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	FVector GetColorFromStates(TArray<EDDB_TileState> states, bool& isFilled);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInstancedStaticMeshComponent> InstancedMesh;

	TArray<FIntPoint> instanceIndexes;

};
