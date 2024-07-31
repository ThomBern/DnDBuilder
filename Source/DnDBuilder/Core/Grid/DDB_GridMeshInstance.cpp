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

void ADDB_GridMeshInstance::AddInstance(FTransform transform, FIntPoint index)
{
	RemoveInstance(index);

	InstancedMesh->AddInstance(transform);

	instanceIndexes.Add(index);
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
