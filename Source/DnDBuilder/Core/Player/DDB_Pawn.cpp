// Fill out your copyright notice in the Description page of Project Settings.


#include "DDB_Pawn.h"

#include "DDB_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADDB_Pawn::ADDB_Pawn()
{	

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ADDB_Pawn::BeginPlay()
{
	Super::BeginPlay();

	locationDesired = GetActorLocation();
	zoomDesired = SpringArm->TargetArmLength;
	rotationDesired = GetActorRotation();
	
}

// Called every frame
void ADDB_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, zoomDesired, DeltaTime, zoomInterpSpeed);

	SetActorLocation(FMath::VInterpTo(GetActorLocation(), locationDesired, DeltaTime, locationInterpSpeed));

	SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotationDesired, DeltaTime, rotationInterpSpeed));
}

// Called to bind functionality to input
void ADDB_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<ADDB_PlayerController>(GetOwner())->GetLocalPlayer());

		InputSubsystem->AddMappingContext(InputMappingContext, 1);

		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ADDB_Pawn::HandleZoom);
		EnhancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ADDB_Pawn::HandleForward);
		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Triggered, this, &ADDB_Pawn::HandleRight);
		EnhancedInputComponent->BindAction(RotationRightAction, ETriggerEvent::Triggered, this, &ADDB_Pawn::HandleRotationRight);
		EnhancedInputComponent->BindAction(RotationLeftAction, ETriggerEvent::Triggered, this, &ADDB_Pawn::HandleRotationLeft);
		
	}
}


void ADDB_Pawn::HandleZoom(const FInputActionValue& value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), value.Get<float>()));

	zoomDesired = FMath::Clamp(zoomDesired + value.Get<float>() * zoomSpeed, zoomMin, zoomMax);
}

void ADDB_Pawn::HandleForward(const FInputActionValue& value)
{
	locationDesired = locationDesired + GetActorForwardVector() * value.Get<float>() * locationSpeed;
}

void ADDB_Pawn::HandleRight(const FInputActionValue& value)
{
	locationDesired = locationDesired + GetActorRightVector() * value.Get<float>() * locationSpeed;
}

void ADDB_Pawn::HandleRotationRight(const FInputActionValue& value)
{
	rotationDesired.Yaw = rotationDesired.Yaw - rotationSpeed; 
}

void ADDB_Pawn::HandleRotationLeft(const FInputActionValue& value)
{
	rotationDesired.Yaw = rotationDesired.Yaw + rotationSpeed; 
}