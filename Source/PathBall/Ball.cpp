// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SocketOffset = FVector(600.f, 0.f, 300.f);
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetupAttachment(DummyRoot);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	CurrentZ = BallMesh->GetRelativeLocation().Z;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentZ > EndZ)			CurrentZ = BallMesh->GetRelativeLocation().Z;
	else if (CurrentZ <= EndZ)	BallMesh->SetSimulatePhysics(false);
}

