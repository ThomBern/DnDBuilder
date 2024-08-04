// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_PlayerActions.h"

#include "Kismet/GameplayStatics.h"

#include "../Grid/DDB_Grid.h"
#include "../Grid/Utilities/DDB_FL_Tile.h"

// Sets default values
ADDB_PlayerActions::ADDB_PlayerActions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADDB_PlayerActions::BeginPlay()
{
	Super::BeginPlay();

	grid = Cast<ADDB_Grid>(UGameplayStatics::GetActorOfClass(GetWorld(), ADDB_Grid::StaticClass()));

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController) {
		EnableInput(PlayerController); 
	}
}

// Called every frame
void ADDB_PlayerActions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHoveredTile();
}

void ADDB_PlayerActions::UpdateHoveredTile()
{
	FIntPoint hoveredCurrently = grid->GetTileIndexUnderCursor(0);
	if (hoveredTile != hoveredCurrently) {
		grid->RemoveStateFromTile(hoveredTile, EDDB_TileState::HOVERED);

		hoveredTile = hoveredCurrently;

		grid->AddStateToTile(hoveredTile, EDDB_TileState::HOVERED);
	}

	if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton)) {
		grid->AddStateToTile(hoveredTile, EDDB_TileState::SELECTED);
	}

	if (PlayerController->IsInputKeyDown(EKeys::RightMouseButton)) {
		grid->RemoveStateFromTile(hoveredTile, EDDB_TileState::SELECTED);
	}

}
