// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_FL_Utilities.h"
#include "Math/UnrealMathUtility.h"

UDDB_FL_Utilities::UDDB_FL_Utilities(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FVector UDDB_FL_Utilities::SnapVectorToVector(FVector v1, FVector v2)
{
    FVector returnVec;

    returnVec.X = FMath::GridSnap(v1.X, v2.X);
    returnVec.Y = FMath::GridSnap(v1.Y, v2.Y);
    returnVec.Z = FMath::GridSnap(v1.Z, v2.Z);

    return returnVec;
}

bool UDDB_FL_Utilities::IsFloatEven(float f)
{
    return FMath::Fmod(f, 2.0) == 0;
}

bool UDDB_FL_Utilities::IsIntEven(int i)
{
    return i % 2 == 0;
}
