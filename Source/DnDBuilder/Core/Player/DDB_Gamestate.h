// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DDB_Gamestate.generated.h"

/**
 * 
 */
UCLASS()
class DNDBUILDER_API ADDB_Gamestate : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADDB_Gamestate();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinCount;
};
