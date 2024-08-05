// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Action.h"

// Sets default values
ADDB_Action::ADDB_Action()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADDB_Action::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDB_Action::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

