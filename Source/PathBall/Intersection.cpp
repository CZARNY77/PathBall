// Fill out your copyright notice in the Description page of Project Settings.


#include "Intersection.h"
#include "PlayerBall.h"
#include "Components/SphereComponent.h"
#include "GameHUD.h"

// Sets default values
AIntersection::AIntersection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinderOptional<UMaterial> White(TEXT("/Game/Materials/WhiteMaterial.WhiteMaterial"));
	static ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Black(TEXT("/Game/Materials/BlackMaterial.BlackMaterial"));

	WhiteMaterial = White.Get();
	BlackMaterial = Black.Get();

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Intersection"));
	MyMesh->SetMaterial(0, WhiteMaterial);
	MyMesh->SetupAttachment(DummyRoot);

	SphereTriggerIn = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTriggerIn"));
	SphereTriggerIn->SetCollisionProfileName("Trigger");
	SphereTriggerIn->SetupAttachment(DummyRoot);

	SphereTriggerOut = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTriggerOut"));
	SphereTriggerOut->SetCollisionProfileName("Trigger");
	SphereTriggerOut->SetupAttachment(DummyRoot);

}

void AIntersection::BeginPlay()
{
	SphereTriggerIn->OnComponentBeginOverlap.AddDynamic(this, &AIntersection::OnBeginOverlap);
	SphereTriggerOut->OnComponentBeginOverlap.AddDynamic(this, &AIntersection::OnBeginOverlapFirst);
	SphereTriggerOut->OnComponentEndOverlap.AddDynamic(this, &AIntersection::OnOverlapEnd);
}

void AIntersection::verification()
{
	if (ClosePath.Num() > 0) {
		int HowManyActivePaths = 0;
		for (int i = 0; i < ClosePath.Num(); i++) {
			if (ClosePath[i]->pIsActive) HowManyActivePaths++;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("Aktywnych = %i"), HowManyActivePaths));
		if (HowManyActivePaths == ClosePath.Num()) {
			MyMesh->SetMaterial(0, BlackMaterial);

			if(Going)
				if (AGameHUD* GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())) {
					GameHUD->TextWinner = FText::FromString("Remis");
					GameHUD->win = true;
				}
		}
	}
}

void AIntersection::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerBall* PB = Cast<APlayerBall>(OtherActor)) {
		Going = true;
		verification();
	}
}

void AIntersection::OnBeginOverlapFirst(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerBall* PB = Cast<APlayerBall>(OtherActor)) {
		PB->Intersection = this;
	}
}
 
void AIntersection::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerBall* PB = Cast<APlayerBall>(OtherActor)) {
		Going = false;
		verification();
		ClosePath.Empty();
	}

}
