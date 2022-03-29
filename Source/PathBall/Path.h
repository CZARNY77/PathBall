// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBall.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

UCLASS()
class PATHBALL_API APath : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Block, VisibledefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere_1;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere_2;

public:	
	// Sets default values for this actor's properties
	APath();

	UPROPERTY()
	class UMaterial* WhiteMaterial;
	UPROPERTY()
	class UMaterialInstance* BlackMaterial;
	UPROPERTY()
	class UMaterialInstance* YellowMaterial;

	bool pIsActive;
	bool IsBall;

	float SphereRadius;

	FVector PathEnd;

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void ONFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void HandleClicked();
	UFUNCTION()
	void HoverOnPath();
	UFUNCTION()
	void GetOutOnPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

	class APlayerBall* Ball;

	UFUNCTION()
	void OnBeginOverlapSphere_1(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBeginOverlapSphere_2(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndSphere_1(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapEndSphere_2(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
