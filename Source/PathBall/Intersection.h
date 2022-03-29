// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Path.h"
#include "Containers/Array.h"
#include "GameFramework/Actor.h"
#include "Intersection.generated.h"


UCLASS()
class PATHBALL_API AIntersection : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* SphereTriggerIn;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* SphereTriggerOut;

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	class UMaterial* WhiteMaterial;
	UPROPERTY()
	class UMaterialInstance* BlackMaterial;

	bool Going;

public:	
	// Sets default values for this actor's properties
	AIntersection();


	TArray <class APath*> ClosePath;

	UFUNCTION()
	void verification();

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBeginOverlapFirst(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
