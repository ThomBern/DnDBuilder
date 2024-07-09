#include "DDB_Gamemode.h"
#include "DDB_Gamestate.h"
#include "DDB_PlayerController.h"
#include "DDB_Pawn.h"

// Définit les valeurs par défaut
ADDB_Gamemode::ADDB_Gamemode()
{
	//// Définissez ce empty pour appeler Tick() à chaque frame. Vous pouvez désactiver cette option pour améliorer les performances si vous n’en avez pas besoin.
	//PrimaryActorTick.bCanEverTick = true;

	GameStateClass = ADDB_Gamestate::StaticClass();
	PlayerControllerClass = ADDB_PlayerController::StaticClass();
	DefaultPawnClass = ADDB_Pawn::StaticClass();

}

/* vv TESTING C++ GAMEMODE STUFF vv */

// int32 ADDB_Gamemode::GetCoins() const 
// {
// 	return GetGameState<ADDB_Gamestate>()->CoinCount;
// }

// void ADDB_Gamemode::SetCoins(int32 newCoins)
// {
// 	GetGameState<ADDB_Gamestate>()->CoinCount = newCoins;
// }

// void ADDB_Gamemode::StartPlay()
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartPlay Default called"));

// 	StartPlayEvent();

// 	/*initialize stuff here*/

// 	Super::StartPlay();
// }

// void ADDB_Gamemode::StartPlayEvent_Implementation()
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartPlayEvent Default Implementation called"));
// }
