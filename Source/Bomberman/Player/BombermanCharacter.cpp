// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Bomb.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ABombermanCharacter::ABombermanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;
	CameraArm->TargetArmLength = 600.f;
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	// Attack stuff
	bCanAttack = true;
	bIsAlive = true;
	AttackCharges = 1;

	// Load the sound
	// This should be done via an audio manager
	/*static ConstructorHelpers::FObjectFinder<USoundCue> BombPlacementSound_BP(TEXT("'/Game/Sounds/Place_Cue.Place_Cue'"));

	PlacementComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio component"));
	PlacementComponent->bAutoActivate = false;
	PlacementComponent->SetupAttachment(RootComponent);*/

}

void ABombermanCharacter::DamageActor_Implementation()
{
	bIsAlive = false;
	GotKilledDelegate.Broadcast();

	APlayerController* PC = Cast<APlayerController>(GetController());
	DisableInput(PC);
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

void ABombermanCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/*if (BombPlacementSound->IsValidLowLevelFast())
	{
		PlacementComponent->SetSound(BombPlacementSound);
	}*/
}

void ABombermanCharacter::Attack()
{
	if (bCanAttack && bIsAlive)
	{
		PlaceBomb();
	}
}

void ABombermanCharacter::BombExploded()
{
	ModifyAmmo(1);
}

void ABombermanCharacter::VerifyAmmo()
{
	bCanAttack = AttackCharges > 0;
}

void ABombermanCharacter::PlaceBomb()
{
	if (EquipedBomb)
	{
		// Do a front check

		FTransform PlayerTransform = GetActorTransform();
		FVector CurrentLocation = PlayerTransform.GetLocation();
		CurrentLocation.X = FGenericPlatformMath::RoundToInt(CurrentLocation.X / 100) * 100;
		CurrentLocation.Y = FGenericPlatformMath::RoundToInt(CurrentLocation.Y / 100) * 100;
		PlayerTransform.SetLocation(CurrentLocation);

		ABomb * SpawnedBomb = GetWorld()->SpawnActor<ABomb>(EquipedBomb, PlayerTransform, FActorSpawnParameters());
		if (SpawnedBomb)
		{
			SpawnedBomb->BombDetonatedDelegate.AddDynamic(this, &ABombermanCharacter::BombExploded);
			ModifyAmmo(-1);
			PlayPlacementSound();
		}
	}
}

void ABombermanCharacter::ModifyAmmo(int32 Modifier)
{
	AttackCharges += Modifier;
	AmmoModifiedDelegate.Broadcast(AttackCharges);
	VerifyAmmo();
}

