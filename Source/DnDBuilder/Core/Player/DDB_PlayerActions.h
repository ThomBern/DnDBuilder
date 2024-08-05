// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Grid/DDB_Grid.h"

#include "DDB_PlayerActions.generated.h"

class ADDB_Action;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectedActionChangedDelegate, ADDB_Action*, LeftClickAction, ADDB_Action*, RightClickAction);
// DECLARE_DELEGATE_TwoParams(FSelectedActionChangedDelegate, ADDB_Action*, ADDB_Action*);


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ADDB_Grid> grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint hoveredTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint selectedTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ADDB_Action> A_LeftClick;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ADDB_Action> A_RightClick;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FSelectedActionChangedDelegate OnSelectedActionChanged;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	void UpdateHoveredTile();

	TObjectPtr<APlayerController> PlayerController;

};
