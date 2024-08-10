// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DDB_Action.h"
#include "DDB_Action_IncDecTileHeight.generated.h"

/**
 * 
 */
UCLASS()
class DNDBUILDER_API ADDB_Action_IncDecTileHeight : public ADDB_Action
{
	GENERATED_BODY()
	
	public:
		virtual void ExecuteAction(FIntPoint index) override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool increase;
};
