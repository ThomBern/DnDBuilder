// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DDB_Gridshape_Data.h"
#include "DDB_TileType.h"

#include "DDB_GridModifier.generated.h"

class UStaticMeshComponent;

UCLASS()
class DNDBUILDER_API ADDB_GridModifier : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADDB_GridModifier();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	EDDB_Gridshape shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	EDDB_TileType tileType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
