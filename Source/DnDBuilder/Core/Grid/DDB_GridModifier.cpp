// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_GridModifier.h"

#include "Components/StaticMeshComponent.h"

#include "Utilities/DDB_FL_Gridshape.h"


// Sets default values
ADDB_GridModifier::ADDB_GridModifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	shape = EDDB_Gridshape::SQUARE;
	tileType = EDDB_TileType::OBSTACLE;
}

// Called when the game starts or when spawned
void ADDB_GridModifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDB_GridModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_GridModifier::OnConstruction(const FTransform &Transform)
{
	if (shape == EDDB_Gridshape::NONE) return;

	FDDB_Gridshape_Data row;
	UDDB_FL_Gridshape::GetShapeData(shape, row);

	// if (!row.mesh) return;

	StaticMesh->SetStaticMesh(row.mesh);
	StaticMesh->SetMaterial(0, row.flatMaterial);

	StaticMesh->SetScalarParameterValueOnMaterials(FName("IsFilled"), 1.f);

	switch (tileType) {
		case EDDB_TileType::NORMAL:
			StaticMesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(1.f,1.f,1.f));
			break;
		case EDDB_TileType::OBSTACLE:
			StaticMesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(0.35f,0.f,0.f));
			break;
		case EDDB_TileType::NONE:
			StaticMesh->SetVectorParameterValueOnMaterials(FName("Color"), FVector(0.f,0.f,0.f));
			break;
	}

	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	SetActorHiddenInGame(true);
}
