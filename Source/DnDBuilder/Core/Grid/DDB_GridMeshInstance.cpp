// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_GridMeshInstance.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


// Sets default values
ADDB_GridMeshInstance::ADDB_GridMeshInstance()
{
	PrimaryActorTick.bStartWithTickEnabled = false;

	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	SetRootComponent(InstancedMesh);

	InstancedMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InstancedMesh->SetCollisionObjectType(ECC_WorldStatic);
	InstancedMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	InstancedMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

	InstancedMesh->NumCustomDataFloats = 4;
	
}

// Called when the game starts or when spawned
void ADDB_GridMeshInstance::BeginPlay()
{
	Super::BeginPlay();

}

void ADDB_GridMeshInstance::InitializeGridMeshInstance(UStaticMesh* mesh, UMaterialInstance* material, FVector color, ECollisionEnabled::Type collision)
{
	InstancedMesh->SetStaticMesh(mesh);
	InstancedMesh->SetMaterial(0, material);
	InstancedMesh->SetVectorParameterValueOnMaterials(FName("Color"), color);
	InstancedMesh->SetCollisionEnabled(collision);
}

// Called every frame
void ADDB_GridMeshInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_GridMeshInstance::AddInstance(FTransform transform, FIntPoint index, TArray<EDDB_TileState> states)
{
	RemoveInstance(index);

	InstancedMesh->AddInstance(transform);

	int32 instanceIndex = instanceIndexes.Add(index);

	bool isFilled = false;
	FVector color = GetColorFromStates(states, isFilled);

	InstancedMesh->SetCustomDataValue(instanceIndex, 0, color.X);
	InstancedMesh->SetCustomDataValue(instanceIndex, 1, color.Y);
	InstancedMesh->SetCustomDataValue(instanceIndex, 2, color.Z);
	if (isFilled)
		InstancedMesh->SetCustomDataValue(instanceIndex, 3, 1.f);


}

void ADDB_GridMeshInstance::RemoveInstance(FIntPoint index)
{
	if (instanceIndexes.Contains(index)) {
		int32 meshIndex = instanceIndexes.Find(index);
		InstancedMesh->RemoveInstance(meshIndex);

		instanceIndexes.Remove(index);
	}
}

void ADDB_GridMeshInstance::ClearInstances()
{
	InstancedMesh->ClearInstances();
	instanceIndexes.Empty();
}

FVector ADDB_GridMeshInstance::GetColorFromStates(TArray<EDDB_TileState> states, bool& isFilled)
{
	if (states.IsEmpty()) return FVector(0.f,0.f,0.f);
	
	TArray<EDDB_TileState> priority = { 
		EDDB_TileState::SELECTED, 
		EDDB_TileState::HOVERED,
		EDDB_TileState::NEIGHBOR
	};
	
	for (EDDB_TileState state : priority) {
		if (states.Contains(state)) {
			isFilled = true;

			switch (state) {
				case EDDB_TileState::SELECTED:
					return FVector(1.f,0.3f, 0.05f);
				case EDDB_TileState::HOVERED:
					return FVector(0.8f,0.6f,0.f);
				case EDDB_TileState::NEIGHBOR:
					return FVector(1.f, 0.3f, 0.7f);
				default:
					return FVector(0.5f, 0.5f, 0.5f);
			}
		}
	}

	return FVector(0.f,0.f,0.f);

}