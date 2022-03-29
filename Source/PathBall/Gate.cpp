// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"
#include "PlayerBall.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "GameHUD.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct GateInfo
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> GateMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GateMaterial;
		GateInfo() :
			GateMesh(TEXT("/Game/Meshs/Cube.Cube")),
			GateMaterial(TEXT("/Game/Materials/GateMaterial.GateMaterial"))
		{}
	};
	GateInfo MyGate;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetStaticMesh(MyGate.GateMesh.Get());
	GateMesh->SetRelativeScale3D(FVector(2.2f, 0.2f, 0.2f));  
	GateMesh->SetMaterial(0, MyGate.GateMaterial.Get());
	GateMesh->SetupAttachment(DummyRoot);

	BorderGate = CreateDefaultSubobject<UBoxComponent>(TEXT("BorderGate"));
	BorderGate->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	BorderGate->SetRelativeScale3D(FVector(7.0f, 0.75f, 0.5f));
	BorderGate->SetCollisionProfileName("Trigger");
	BorderGate->SetupAttachment(DummyRoot);
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
	
	BorderGate->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnBeginOverlap);
}

// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerBall* Ball = Cast<APlayerBall>(OtherActor)) {
		if (PlayerGate == 1) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Wygral gracz 2")));
			if (AGameHUD* GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())) {
				GameHUD->TextWinner = FText::FromString("Wygral gracz 2");
				GameHUD->win = true;
			}
		}
		else if (PlayerGate == 2) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Wygral gracz 1")));
			if (AGameHUD* GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())) {
				GameHUD->TextWinner = FText::FromString("Wygral gracz 1");
				GameHUD->win = true;
			}
		}
	}
}

