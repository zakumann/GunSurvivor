#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	EnemyFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EnemyFlipbook"));
	EnemyFlipbook->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Player)
	{
		AActor *PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATopdownCharacter::StaticClass());
		if (PlayerActor)
		{
			Player = Cast<ATopdownCharacter>(PlayerActor);
			CanFollow = true;
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAlive && CanFollow && Player)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		FVector DirectionToPlayer = PlayerLocation - CurrentLocation;
		float DistanceToPlayer = DirectionToPlayer.Length();

		if (DistanceToPlayer >= StopDistance)
		{
			DirectionToPlayer.Normalize();
			FVector NewLocation = CurrentLocation + (DirectionToPlayer * MoementSpeed * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

