// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBall.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"

// Sets default values
APlayerBall::APlayerBall()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCamera"));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APlayerBall::BeginPlay()
{
	Super::BeginPlay();
	MoveLocation = FVector(0.f, 0.f, 80.f);
	Player = 1;
}

void APlayerBall::WhatPlayer()
{
	if (Player == 1) Player = 2;
	else if (Player == 2) Player = 1;
}

void APlayerBall::MoveCamera(float X, float Y)
{
	MCamera = true;
	EndLocationX = X;
	EndLocationY = Y;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Kick, GetActorLocation(), 0.5f, 1.0f, 0.f);
}

void APlayerBall::Pause()
{
	if (AGameHUD* GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())) {
		if (GameHUD->pause)		GameHUD->pause = false;
		else					GameHUD->pause = true;

		GameHUD->CheckPause();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Jej")));
	}
}

void APlayerBall::ScrollCamera(float Val)
{
	if ((SpringArm->GetSocketLocation("ArmCamera").Z <= 1000 || Val > 0) && (SpringArm->GetSocketLocation("ArmCamera").Z >= 200 || Val < 0))
		SpringArm->SocketOffset += FVector(Val * 10, 0.f, 0.f);
}

void APlayerBall::MoveForward(float Val)
{
	if ((SpringArm->GetSocketLocation("ArmCamera").X <= 800 || Val < 0) && (SpringArm->GetSocketLocation("ArmCamera").X >= -800 || Val > 0))
		MoveF = Val * 300;
	else
		MoveF = 0.f;
	//Camera->AddLocalOffset(FVector(Val*10, 0.f, 0.f));
}

void APlayerBall::MoveRight(float Val)
{
	if ((SpringArm->GetSocketLocation("ArmCamera").Y <= 600 || Val < 0) && (SpringArm->GetSocketLocation("ArmCamera").Y >= -600 || Val > 0))
		MoveR = Val * 300;
	else
		MoveR = 0.f;
	//Camera->AddLocalOffset(FVector( 0.f, Val * 10, 0.f));
}

// Called every frame
void APlayerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), MoveLocation);

	if (MCamera) {
		float CameraY = SpringArm->GetComponentLocation().Y;
		if (!FMath::IsNearlyEqual(CameraY, EndLocationY, 10.0f)) {
			float temp = CameraY > EndLocationY ? -1 : 1;
			SpringArm->AddLocalOffset(FVector(0.f, (1000 * temp) * DeltaTime, 0.f));
			
		}
		else bCameraY = true;

		float CameraX = SpringArm->GetComponentLocation().X;
		if (!FMath::IsNearlyEqual(CameraX, EndLocationX, 10.0f)) {
			float temp = CameraX > EndLocationX ? -1 : 1;
			SpringArm->AddLocalOffset(FVector(0.f, 0.f, (1000 * temp) * DeltaTime));
			
		}
		else bCameraX = true;

		if (bCameraX && bCameraY) {
			MCamera = false;
			bCameraX = false;
			bCameraY = false;
		}
	}
	else SpringArm->AddLocalOffset(FVector(0.f, MoveR * DeltaTime, MoveF * DeltaTime));

}

// Called to bind functionality to input
void APlayerBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Scroll", this, &APlayerBall::ScrollCamera);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerBall::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerBall::MoveRight);

	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &APlayerBall::Pause);

}