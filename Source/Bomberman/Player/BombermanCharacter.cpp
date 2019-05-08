// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Bomb.h"
#include "Engine/World.h"

// Sets default values
ABombermanCharacter::ABombermanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;
	CameraArm->TargetArmLength = 800.f;
	CameraArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	// Attack stuff
	bCanAttack = true;
	AttackCharges = 1;
}

// Called when the game starts or when spawned
void ABombermanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombermanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABombermanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABombermanCharacter::Attack()
{
	if (bCanAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tried to spawn a bomb"));

		if (EquipedBomb)
		{
			// Do a front check

			FTransform PlayerTransform = GetActorTransform();
			FVector CurrentLocation = PlayerTransform.GetLocation();
			CurrentLocation.X = FGenericPlatformMath::RoundToInt(CurrentLocation.X / 100) * 100;
			CurrentLocation.Y = FGenericPlatformMath::RoundToInt(CurrentLocation.Y / 100) * 100;
			PlayerTransform.SetLocation(CurrentLocation);

			ABomb* SpawnedBomb = GetWorld()->SpawnActor<ABomb>(EquipedBomb, PlayerTransform, FActorSpawnParameters());
			if (SpawnedBomb)
			{
				UE_LOG(LogTemp, Warning, TEXT("Player spawned a bomb"));
				
			}
		}

	}
}

