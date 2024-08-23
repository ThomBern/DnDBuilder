// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/TextRenderActor.h"

#include "DDB_TileDebugText.generated.h"

class ADDB_Grid;

UCLASS()
class DNDBUILDER_API ADDB_TileDebugText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_TileDebugText();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SetShowTileIndexes(bool showIndexes);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ADDB_Grid> grid;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FIntPoint, ATextRenderActor*> spawnedTexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowTileIndexes;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	ATextRenderActor* GetTextActor(FIntPoint index);
	void DestroyTextActor(FIntPoint index);
	void ClearAllTextActors();
	void UpdateTileText(FIntPoint index);

};
