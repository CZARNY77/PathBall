// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));
	RootComponent = DummyRoot;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(RootComponent);

	Dimensions = FVector(300, 0, 0);
	AxisVector = FVector(0, 0, 0);
	Multiplier = 10.f;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(-170, 0, 80);

	AngleAxis += DeltaTime * Multiplier;

	if (AngleAxis >= 360.0f)
	{
		AngleAxis = 0;
	}

	FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, AxisVector);

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	FRotator NewRotation = FRotator(-15, AngleAxis, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);


}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

