// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "DDB_Pawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DNDBUILDER_API ADDB_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADDB_Pawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input|Camera Movement")
	TObjectPtr<UInputAction> ZoomAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input|Camera Movement")
	TObjectPtr<UInputAction> ForwardAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input|Camera Movement")
	TObjectPtr<UInputAction> RightAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input|Camera Movement")
	TObjectPtr<UInputAction> RotationRightAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input|Camera Movement")
	TObjectPtr<UInputAction> RotationLeftAction = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HandleZoom(const FInputActionValue& value);
	void HandleForward(const FInputActionValue& value);
	void HandleRight(const FInputActionValue& value);
	void HandleRotationRight(const FInputActionValue& value);
	void HandleRotationLeft(const FInputActionValue& value);

private:

	UPROPERTY(VisibleAnywhere)
	float zoomDesired;

	UPROPERTY(VisibleAnywhere)
	FVector locationDesired;

	UPROPERTY(VisibleAnywhere)
	FRotator rotationDesired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

};
