// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_TileDebugText.h"

#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

#include "../../Core/Grid/DDB_Grid.h"
// #include "../../Core/Grid/Utilities/DDB_FL_Tile.h"

// Sets default values
ADDB_TileDebugText::ADDB_TileDebugText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ADDB_TileDebugText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ADDB_TileDebugText::BeginPlay()
{
	Super::BeginPlay();
	
	grid = Cast<ADDB_Grid>(UGameplayStatics::GetActorOfClass(GetWorld(), ADDB_Grid::StaticClass()));

	grid->OnTileDataUpdated.BindUObject(this, &ADDB_TileDebugText::UpdateTileText);
	grid->OnGridDestroyed.BindUObject(this, &ADDB_TileDebugText::ClearAllTextActors);
}

ATextRenderActor* ADDB_TileDebugText::GetTextActor(FIntPoint index)
{
	ATextRenderActor** actor = spawnedTexts.Find(index);

	if (actor) {
		return *actor;
	}
	
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.Owner = grid;
	ATextRenderActor* newActor = GetWorld()->SpawnActor<ATextRenderActor>(FVector(), FRotator(), params);

	newActor->SetActorTickEnabled(false);
	newActor->SetActorEnableCollision(false);

	newActor->GetTextRender()->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	newActor->GetTextRender()->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	
	spawnedTexts.Add(index, newActor);

    return newActor;
}

void ADDB_TileDebugText::DestroyTextActor(FIntPoint index)
{
	ATextRenderActor** actor = spawnedTexts.Find(index);

	if (actor) {
		(*actor)->Destroy();
		spawnedTexts.Remove(index);
	}
}

void ADDB_TileDebugText::ClearAllTextActors()
{
	for (const TPair<FIntPoint, ATextRenderActor*>& text : spawnedTexts) {
		text.Value->Destroy();
	}

	spawnedTexts.Empty();
}

void ADDB_TileDebugText::UpdateTileText(FIntPoint index)
{
	if (!bShowTileIndexes) return;
	
	if (FDDB_Tile_Data* data = grid->gridTiles.Find(index)) {

		if (!UDDB_FL_Tile::IsTileTypeWalkable(data->type)) {
			DestroyTextActor(index);
			return;
		}

		ATextRenderActor* textActor = GetTextActor(index);
		FString text = FString::Printf(TEXT("%d , %d"), index.X, index.Y);

		textActor->GetTextRender()->SetText(FText::FromString(text));

		textActor->SetActorLocation(data->transform.GetLocation() + FVector(0.f,0.f,1.f));
		textActor->SetActorRotation(FQuat(FRotator(90.f,180.f,0.f)));
		textActor->SetActorScale3D(FVector(2.f));
	}
	else {
		DestroyTextActor(index);
	}
}

void ADDB_TileDebugText::SetShowTileIndexes(bool showIndexes)
{
	bShowTileIndexes = showIndexes;

	if (bShowTileIndexes) {
		TArray<FIntPoint> indexes;
		grid->gridTiles.GetKeys(indexes);

		for (FIntPoint index : indexes) {
			UpdateTileText(index);
		}
	} 
	else {
		ClearAllTextActors();
	}
}
