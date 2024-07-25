#include "TopdownCharacter.h"

ATopdownCharacter::ATopdownCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	CharacterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CharacterFlipbook"));
	CharacterFlipbook->SetupAttachment(RootComponent);
}

void ATopdownCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ATopdownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATopdownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATopdownCharacter::MoveTriggered);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &ATopdownCharacter::MoveCompleted);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Canceled, this, &ATopdownCharacter::MoveCompleted);

		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Started, this, &ATopdownCharacter::Shoot);
		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &ATopdownCharacter::Shoot);
	}
}

void ATopdownCharacter::MoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, MoveActionValue.ToString());
}

void ATopdownCharacter::MoveCompleted(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("MoveCompleted"));
}

void ATopdownCharacter::Shoot(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shoot"));
}

