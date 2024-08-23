// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_PlayerActions.h"

#include "Kismet/GameplayStatics.h"

#include "../Grid/Utilities/DDB_FL_Tile.h"

#include "Actions/Grid/DDB_Action_SelectTile.h"

// Sets default values
ADDB_PlayerActions::ADDB_PlayerActions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OnHoveredTileChanged.AddDynamic(this, &ADDB_PlayerActions::HoldAction);
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

	TSubclassOf<ADDB_Action> A_selectTile = ADDB_Action_SelectTile::StaticClass();

	SetSelectedActions(A_selectTile, nullptr);
}

// Called every frame
void ADDB_PlayerActions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController->PlayerInput->WasJustReleased(EKeys::LeftMouseButton.GetFName())) {
		leftClickPressed = false;
	}
	if (PlayerController->PlayerInput->WasJustReleased(EKeys::RightMouseButton.GetFName())) {
		rightClickPressed = false;
	}


	if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton) && A_LeftClick && !leftClickPressed) {
		leftClickPressed = true;
		A_LeftClick->ExecuteAction(hoveredTile);
	}
	if (PlayerController->IsInputKeyDown(EKeys::RightMouseButton) && A_RightClick && !rightClickPressed) {
		rightClickPressed = true;
		A_RightClick->ExecuteAction(hoveredTile);
	}

	UpdateHoveredTile();
}

void ADDB_PlayerActions::SetSelectedActions(TSubclassOf<ADDB_Action> leftAction, TSubclassOf<ADDB_Action> rightAction)
{
	if (A_LeftClick) {
		A_LeftClick->Destroy();
		A_LeftClick = nullptr;
	}
	
	FActorSpawnParameters params;
	params.Owner = this;

	if (leftAction) {
		A_LeftClick = GetWorld()->SpawnActor<ADDB_Action>(leftAction, FTransform(), params);

		if (A_LeftClick) {
			A_LeftClick->playerActions = this;
		}
	}

	if (A_RightClick) {
		A_RightClick->Destroy();
		A_RightClick = nullptr;
	}

	if (leftAction) {
		A_RightClick = GetWorld()->SpawnActor<ADDB_Action>(rightAction, FTransform(), params);
		
		if (A_RightClick) {
			A_RightClick->playerActions = this;
		}
	}

	OnSelectedActionsChanged.Broadcast(A_LeftClick, A_RightClick);
}

void ADDB_PlayerActions::HoldAction()
{
	if (A_LeftClick && leftClickPressed) {
		A_LeftClick->ExecuteAction(hoveredTile);
	}

	if (A_RightClick && rightClickPressed) {
		A_RightClick->ExecuteAction(hoveredTile);
	}
}

void ADDB_PlayerActions::UpdateHoveredTile()
{
	FIntPoint hoveredCurrently = grid->GetTileIndexUnderCursor(0);
	if (hoveredTile != hoveredCurrently) {
		grid->RemoveStateFromTile(hoveredTile, EDDB_TileState::HOVERED);

		hoveredTile = hoveredCurrently;

		grid->AddStateToTile(hoveredTile, EDDB_TileState::HOVERED);

		if (OnHoveredTileChanged.IsBound()) {
			OnHoveredTileChanged.Broadcast();
		}
	}
}
