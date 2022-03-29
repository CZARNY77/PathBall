// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intersection.h"
#include "GameFramework/Character.h"
#include "PlayerBall.generated.h"

UCLASS()
class PATHBALL_API APlayerBall : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USoundBase* Kick;

public:
	// Sets default values for this character's properties
	APlayerBall();

	FVector MoveLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Player;

	UFUNCTION()
	void WhatPlayer();
	UFUNCTION()
	void MoveCamera(float X, float Y);
	UFUNCTION()
	void Pause();

	
	class AIntersection* Intersection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ScrollCamera(float Val);
	UFUNCTION()
	void MoveForward(float Val);
	UFUNCTION()
	void MoveRight(float Val);

	bool MCamera;
	bool bCameraX;
	bool bCameraY;

	float MoveF;
	float MoveR;
	float EndLocationX;
	float EndLocationY;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
