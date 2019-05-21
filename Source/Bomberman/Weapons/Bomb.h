// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UDamageableActor.h"
#include "Bomb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBombDetonatedDelegate);

UCLASS()
class BOMBERMAN_API ABomb : public AActor, public IUDamageableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	// The interface stuff.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DamageControl")
		void DamageActor();
	virtual void DamageActor_Implementation() override;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BombInfo)
		uint32 bAlreadyDetonated : 1;

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintAssignable)
		FBombDetonatedDelegate BombDetonatedDelegate;

};
