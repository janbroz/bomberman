// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateMesh();

	void AvoidInitialOverlap();

	UFUNCTION()
		void OnBombBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnBombEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The bomb we spawned may have some modifiers
	void ApplyModifiers();
	// Begin the bomb detonation.
	void ActivateFuse();
	// Detonate the bomb
	void Detonate();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BombInfo)
		class UStaticMeshComponent* BombMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BombInfo)
		int32 Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BombInfo)
		float Timer;

	FTimerHandle TimerHandle;

};
