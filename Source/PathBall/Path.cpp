// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "Intersection.h"
#include "Components/SphereComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "PlayerBall.h"

// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatic
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> WhiteMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlackMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> YellowMaterial;
		FConstructorStatic() :
			PlaneMesh(TEXT("/Game/Meshs/Cube.Cube")),
			WhiteMaterial(TEXT("/Game/Materials/WhiteMaterial.WhiteMaterial")),
			BlackMaterial(TEXT("/Game/Materials/BlackMaterial.BlackMaterial")),
			YellowMaterial(TEXT("/Game/Materials/YellowMaterial.YellowMaterial"))
		{}
	};
	static FConstructorStatic ConstructorStatics;

	WhiteMaterial = ConstructorStatics.WhiteMaterial.Get();
	BlackMaterial = ConstructorStatics.BlackMaterial.Get();
	YellowMaterial = ConstructorStatics.YellowMaterial.Get();

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 0.2f, 0.2f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetMaterial(0, WhiteMaterial);
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &APath::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &APath::ONFingerPressedBlock);

	IsBall = false;
	pIsActive = false;

	Sphere_1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_1"));
	Sphere_1->InitSphereRadius(30.f);
	Sphere_1->SetCollisionProfileName("Trigger");
	Sphere_1->SetRelativeLocation(FVector(100.f, 0.f, 20.f));
	Sphere_1->SetupAttachment(DummyRoot);

	Sphere_2 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_2"));
	Sphere_2->InitSphereRadius(30.f);
	Sphere_2->SetCollisionProfileName("Trigger");
	Sphere_2->SetRelativeLocation(FVector(-100.f, 0.f, 20.f));
	Sphere_2->SetupAttachment(DummyRoot);

}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere_1->OnComponentBeginOverlap.AddDynamic(this, &APath::OnBeginOverlapSphere_1);
	Sphere_2->OnComponentBeginOverlap.AddDynamic(this, &APath::OnBeginOverlapSphere_2);
	Sphere_1->OnComponentEndOverlap.AddDynamic(this, &APath::OnOverlapEndSphere_1);
	Sphere_2->OnComponentEndOverlap.AddDynamic(this, &APath::OnOverlapEndSphere_2);
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APath::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}
void APath::ONFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void APath::HandleClicked()
{
	if (!pIsActive && IsBall) {
		pIsActive = true;
		BlockMesh->SetMaterial(0, BlackMaterial);
		Ball->MoveLocation = PathEnd;
		Ball->WhatPlayer();
		Ball->MoveCamera(PathEnd.X, PathEnd.Y);
	}
}

void APath::HoverOnPath()
{
	if(!pIsActive)	BlockMesh->SetMaterial(0, YellowMaterial);
}

void APath::GetOutOnPath()
{
	if (!pIsActive)	BlockMesh->SetMaterial(0, WhiteMaterial);
}

void APath::OnBeginOverlapSphere_1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Ball = Cast<APlayerBall>(OtherActor);
	if (Ball) {
		IsBall = true;
		PathEnd = Sphere_2->GetComponentLocation();
		if (AIntersection* IS = Cast<AIntersection>(Ball->Intersection)) {
			IS->ClosePath.Add(this);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("ClosePath = %i"), IS->ClosePath.Num()));
		}
	}
}

void APath::OnBeginOverlapSphere_2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Ball = Cast<APlayerBall>(OtherActor);
	if (Ball) {
		IsBall = true;
		PathEnd = Sphere_1->GetComponentLocation();
		if (AIntersection* IS = Cast<AIntersection>(Ball->Intersection)) {
			IS->ClosePath.Add(this);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("ClosePath = %i"), IS->ClosePath.Num()));
		}
	}
}

void APath::OnOverlapEndSphere_1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Ball) {
		IsBall = false;
	}
}

void APath::OnOverlapEndSphere_2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Ball) {
		IsBall = false;
	}
}

