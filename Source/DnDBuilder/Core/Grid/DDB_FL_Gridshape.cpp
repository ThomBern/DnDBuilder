// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_FL_Gridshape.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/DataTableFunctionLibrary.h"

#include "DDB_Gridshape_Data.h"

TObjectPtr<UDataTable> UDDB_FL_Gridshape::gridDT = nullptr;

UDDB_FL_Gridshape::UDDB_FL_Gridshape(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

    if(!gridDT) {
        static ConstructorHelpers::FObjectFinder<UDataTable> 
            gridShapeRef(TEXT("DataTable'/Game/Blueprint/Core/DDB_DT_Gridshape_Data.DDB_DT_Gridshape_Data'"));

        if (!gridShapeRef.Object) {
            UE_LOG(LogTemp, Warning, TEXT("Gridshape DT not found; returning from SpawnGrid method"));		

            return;
        }
	    
        gridDT = gridShapeRef.Object;
    }
}

bool UDDB_FL_Gridshape::GetShapeData(EDDB_Gridshape gridShape, FDDB_Gridshape_Data& outRow)
{
	FText rowName;
	UEnum::GetDisplayValueAsText(gridShape, rowName);

    FDDB_Gridshape_Data* row = gridDT->FindRow<FDDB_Gridshape_Data>(FName(rowName.ToString()), "");

    if (row) {
        outRow = *row;
        return true;
    }
    else {
		UE_LOG(LogTemp, Error, TEXT("Row not found; GetCurrentShapeData called"));		
        return false;
    }
}
