// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_LevelLoading.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADDB_LevelLoading::ADDB_LevelLoading()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	loadedLevel = "L_Square";
}

// Called when the game starts or when spawned
void ADDB_LevelLoading::BeginPlay()
{
	Super::BeginPlay();

	LoadLevel(loadedLevel, true);

}

// Called every frame
void ADDB_LevelLoading::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDB_LevelLoading::LoadLevel(const FName& levelName, bool bForceLoading)
{
	if (levelName == loadedLevel && !bForceLoading) return;

	// UNLOAD
	ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(this, loadedLevel);
	if (level) {
		level->SetShouldBeLoaded(false);
		level->SetShouldBeVisible(false);
	}

	if (loadedLevel != "" && !level) {
		UE_LOG(LogTemp, Warning, TEXT("Level to unload is not valid"));		
		return;
	}


	// LOAD
	loadedLevel = levelName;
	level = UGameplayStatics::GetStreamingLevel(this, levelName);
	if (!level && levelName != "None") {
		UE_LOG(LogTemp, Warning, TEXT("Level to load is not valid"));		
		return;
	}
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);

}
