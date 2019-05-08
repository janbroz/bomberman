// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS()
class BOMBERMAN_API ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABombermanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// attempts to spawn a bomb
	void Attack();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		TSubclassOf<class ABomb> EquipedBomb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		uint32 bCanAttack : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterConfig)
		int32 AttackCharges;

private:
	UPROPERTY()
		class UCameraComponent* Camera;
	UPROPERTY()
		class USpringArmComponent* CameraArm;

};
