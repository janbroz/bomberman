// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanController.h"
#include "Player/BombermanCharacter.h"
#include "Widgets/Player/PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"

ABombermanController::ABombermanController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUD_BP(TEXT("/Game/Blueprints/UI/HUD/PlayerHUD_BP.PlayerHUD_BP_C"));
	if (PlayerHUD_BP.Object)
	{
		HUDClass = PlayerHUD_BP.Object;
	}
}

void ABombermanController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ABombermanController::PrimaryAttack);
	InputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ABombermanController::SecondaryAttack);

	InputComponent->BindAxis("HorizontalMovement", this, &ABombermanController::HorizontalMovement);
	InputComponent->BindAxis("VerticalMovement", this, &ABombermanController::VerticalMovement);
}

void ABombermanController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AlignToSight();
}

void ABombermanController::BeginPlay()
{
	if (HUDClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(this, HUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

void ABombermanController::HorizontalMovement(float Amount)
{
	if (Amount != 0.f)
	{
		ABombermanCharacter* Bomberman = Cast<ABombermanCharacter>(GetPawn());
		if (Bomberman && Bomberman->bIsAlive)
		{
			Bomberman->AddMovementInput(FVector::RightVector, Amount);
		}
	}
}

void ABombermanController::VerticalMovement(float Amount)
{
	if (Amount != 0.f)
	{
		ABombermanCharacter* Bomberman = Cast<ABombermanCharacter>(GetPawn());
		if (Bomberman && Bomberman->bIsAlive)
		{
			Bomberman->AddMovementInput(FVector::ForwardVector, Amount);
		}
		
	}
}

void ABombermanController::PrimaryAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("Primary attack"));
	ABombermanCharacter* Bomberman = Cast<ABombermanCharacter>(GetPawn());
	if (Bomberman && Bomberman->bIsAlive)
	{
		Bomberman->Attack();
	}
}

void ABombermanController::SecondaryAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Secondary attack"));
	
	
}

void ABombermanController::AlignToSight()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (Hit.bBlockingHit)
	{
		ACharacter* Bomberman = GetCharacter();
		if (Bomberman)
		{
			FVector InitLoc = Bomberman->GetActorLocation();
			FRotator LookAt = (Hit.Location - InitLoc).Rotation();
			FRotator MyRot = GetControlRotation();
			MyRot.Yaw = LookAt.Yaw;
			SetControlRotation(MyRot);
		}
	}
}

