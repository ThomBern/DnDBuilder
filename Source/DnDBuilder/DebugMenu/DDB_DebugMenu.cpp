// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_DebugMenu.h"

#include "Kismet/GameplayStatics.h"

#include "Other/DDB_TileDebugText.h"
#include "Components/ChildActorComponent.h"

// Sets default values
ADDB_DebugMenu::ADDB_DebugMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CA_TileText = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor_TileText"));
	CA_TileText->SetupAttachment(RootComponent);

	CA_TileText->SetChildActorClass(ADDB_TileDebugText::StaticClass());
}

// Called when the game starts or when spawned
void ADDB_DebugMenu::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADDB_DebugMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

