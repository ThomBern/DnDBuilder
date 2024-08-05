// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../DDB_PlayerActions.h"

#include "DDB_Action.generated.h"

UCLASS()
class DNDBUILDER_API ADDB_Action : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_Action();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExecuteAction(FIntPoint index) {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn=true))	
	TObjectPtr<ADDB_PlayerActions> playerActions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
