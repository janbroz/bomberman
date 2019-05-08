// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameModeBase.h"
#include "Player/BombermanCharacter.h"
#include "Player/BombermanController.h"
#include "UObject/ConstructorHelpers.h"

ABombermanGameModeBase::ABombermanGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UClass> Bomberman_BP(TEXT("/Game/Blueprints/Character/Prototype/TestCharacter_BP.TestCharacter_BP_C"));
	if (Bomberman_BP.Object)
	{
		DefaultPawnClass = Bomberman_BP.Object;
	}
	else
	{
		DefaultPawnClass = ABombermanCharacter::StaticClass();
	}

	PlayerControllerClass = ABombermanController::StaticClass();
}
