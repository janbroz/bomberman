// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/UDamageableActor.h"
#include "BombermanCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDiedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerAmmoModified, int32, Ammo);

UCLASS()
class BOMBERMAN_API ABombermanCharacter : public ACharacter, public IUDamageableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABombermanCharacter();

	// The interface stuff.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DamageControl")
		void DamageActor();
	virtual void DamageActor_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	// attempts to spawn a bomb
	void Attack();

	// A bomb exploded and we get 1 ammo back;
	UFUNCTION()
		void BombExploded();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayPlacementSound();

private:
	void VerifyAmmo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		TSubclassOf<class ABomb> EquipedBomb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		int32 AttackCharges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		uint32 bCanAttack : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		uint32 bIsAlive : 1;
	UPROPERTY(BlueprintAssignable)
		FPlayerDiedDelegate GotKilledDelegate;
	UPROPERTY(BlueprintAssignable)
		FPlayerAmmoModified AmmoModifiedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundCue* BombPlacementSound;

	class UAudioComponent* PlacementComponent;

private:
	UPROPERTY()
		class UCameraComponent* Camera;
	UPROPERTY()
		class USpringArmComponent* CameraArm;

	// Spawn a Bomb
	void PlaceBomb();
	void ModifyAmmo(int32 Modifier);

};
