// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Public/TimerManager.h"
#include "Player/BombermanCharacter.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb mesh"));
	RootComponent = BombMesh;
	//BombMesh->SetupAttachment(RootComponent);
	BombMesh->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBombBeginOverlap);
	BombMesh->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnBombEndOverlap);

	Timer = 2.f;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	AvoidInitialOverlap();

	ActivateFuse();
}

void ABomb::RotateMesh()
{
	BombMesh->AddLocalRotation(FRotator(0.f, 1.f, 0.f).Quaternion());
}

void ABomb::AvoidInitialOverlap()
{
	// We want to make sure that if we are colliding with something the collision is disabled.

	BombMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BombMesh->SetCollisionProfileName(TEXT("OverlapAll"));
}

void ABomb::OnBombBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlaped with something"));
}

void ABomb::OnBombEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// We want the player to initially be able to move through the bombs, and then collide with them!
	ABombermanCharacter* Player = Cast<ABombermanCharacter>(OtherActor);
	if (Player)
	{
		BombMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BombMesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateMesh();
}

void ABomb::ApplyModifiers()
{
	
}

void ABomb::ActivateFuse()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABomb::Detonate, Timer, false);


}

void ABomb::Detonate()
{
	UE_LOG(LogTemp, Warning, TEXT("Boom"));
	Destroy();
}
