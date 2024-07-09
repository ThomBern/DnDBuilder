#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DDB_Gamemode.generated.h"

UCLASS()
class DNDBUILDER_API ADDB_Gamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADDB_Gamemode();


	/* vv TESTING C++ GAMEMODE STUFF vv */

	// UFUNCTION(BlueprintPure, Category = "Coins")
	// 	virtual int32 GetCoins() const;

	// UFUNCTION(BlueprintCallable, Category = "Coins")
	// 	virtual void SetCoins(int32 newCoins);

	// virtual void StartPlay();

	// UFUNCTION(BlueprintNativeEvent, Category = "Coins", DisplayName = "Start Play")
	// 	void StartPlayEvent();
	// void StartPlayEvent_Implementation();

};
