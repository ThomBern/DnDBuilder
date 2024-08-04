// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "DDB_PlayerActions.generated.h"

class ADDB_Grid;

UCLASS()
class DNDBUILDER_API ADDB_PlayerActions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_PlayerActions();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ADDB_Grid> grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint hoveredTile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	void UpdateHoveredTile();

	TObjectPtr<APlayerController> PlayerController;
};
