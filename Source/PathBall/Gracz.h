// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gracz.generated.h"

UCLASS()
class PATHBALL_API AGracz : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Component")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	AGracz();

	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* BallMesh;

	bool Kick;
	FVector VSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CurrentZ;

	UPROPERTY(EditAnywhere, Category = "Component")
	float EndZ;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
