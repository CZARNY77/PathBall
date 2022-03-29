// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPlayer {
	Empty,
	Player_1,
	Player_2
};

UCLASS()
class PATHBALL_API AGate : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Component")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* GateMesh;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UBoxComponent* BorderGate;

public:	
	// Sets default values for this actor's properties
	AGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (BitMask, BitmaskEnum = "EPlayer"))
	int32 PlayerGate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
