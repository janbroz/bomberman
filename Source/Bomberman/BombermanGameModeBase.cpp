// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameModeBase.h"
#include "Player/BombermanCharacter.h"
#include "Player/BombermanController.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

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



void ABombermanGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerDelegates();
}

void ABombermanGameModeBase::SetupPlayerDelegates()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		ABombermanCharacter* Char = Cast<ABombermanCharacter>(PC->GetCharacter());
		if (Char)
		{
			Char->GotKilledDelegate.AddDynamic(this, &ABombermanGameModeBase::PlayerDied);
		}
	}
}

void ABombermanGameModeBase::BeginRound()
{

}

void ABombermanGameModeBase::PlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("The player got killed"));
}
