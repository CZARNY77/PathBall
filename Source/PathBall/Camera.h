// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

UCLASS()
class PATHBALL_API ACamera : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Component")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	ACamera();

	UPROPERTY(EditAnywhere, Category = Movement)
	float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Multiplier;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
