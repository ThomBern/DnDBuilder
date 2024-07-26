// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DDB_LevelLoading.generated.h"

UCLASS()
class DNDBUILDER_API ADDB_LevelLoading : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDB_LevelLoading();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LoadLevel(const FName& levelName, bool bForceLoading = false);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Vars")
	FName loadedLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

};
