// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Grid/DDB_Grid.h"

#include "DDB_PlayerActions.generated.h"

class ADDB_Action;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectedActionsChangedDelegate, ADDB_Action*, LeftClickAction, ADDB_Action*, RightClickAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHoveredTileChangedDelegate);


UCLASS()
class DNDBUILDER_API ADDB_PlayerActions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_PlayerActions();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetSelectedActions(TSubclassOf<ADDB_Action> leftAction, TSubclassOf<ADDB_Action> rightAction);
	
	UFUNCTION()
	void HoldAction();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ADDB_Grid> grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint hoveredTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint selectedTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ADDB_Action> A_LeftClick;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ADDB_Action> A_RightClick;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FSelectedActionsChangedDelegate OnSelectedActionsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FHoveredTileChangedDelegate OnHoveredTileChanged;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	void UpdateHoveredTile();

	TObjectPtr<APlayerController> PlayerController;

	bool leftClickPressed, rightClickPressed = false;
};
