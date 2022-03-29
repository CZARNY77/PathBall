// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PATHBALL_API ABall : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Component")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UCameraComponent* Camera;

public:	
	// Sets default values for this actor's properties
	ABall();

	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* BallMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CurrentZ;

	UPROPERTY(EditAnywhere, Category = "Component")
	float EndZ;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
