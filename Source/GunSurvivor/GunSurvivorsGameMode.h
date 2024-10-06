// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GunSurvivorsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUNSURVIVOR_API AGunSurvivorsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Score = 0;

	AGunSurvivorsGameMode();
	virtual void BeginPlay() override;

	void SetScore(int NewScore);
	void AddScore(int AmountToAdd);
};
