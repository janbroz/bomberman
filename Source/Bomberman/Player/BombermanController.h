// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BombermanController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanController : public APlayerController
{
	GENERATED_BODY()
public:
	ABombermanController();


public:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UFUNCTION()
		void HorizontalMovement(float Amount);
	UFUNCTION()
		void VerticalMovement(float Amount);
	UFUNCTION()
		void PrimaryAttack();
	UFUNCTION()
		void SecondaryAttack();


	TSubclassOf<class UPlayerHUD> HUDClass;
	class UPlayerHUD* PlayerHUD;

private:
	void AlignToSight();

};
