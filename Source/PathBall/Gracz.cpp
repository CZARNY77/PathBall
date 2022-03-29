// Fill out your copyright notice in the Description page of Project Settings.


#include "Gracz.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGracz::AGracz()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetupAttachment(DummyRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SocketOffset = FVector(600.f, 0.f, 300.f);
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(BallMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AGracz::BeginPlay()
{
	Super::BeginPlay();
	CurrentZ = BallMesh->GetRelativeLocation().Z;
	Kick = false;
}

// Called every frame
void AGracz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentZ > EndZ)		CurrentZ = BallMesh->GetRelativeLocation().Z;
	else if (CurrentZ <= EndZ)	BallMesh->SetSimulatePhysics(false);

	if (Kick) {
		VSphere.Z = 0.f;
		DummyRoot->AddRelativeLocation(VSphere/10);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("if")));
	}
	else if (DummyRoot->GetRelativeLocation() == VSphere) {
		Kick = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("else if")));
	}
}

// Called to bind functionality to input
void AGracz::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

