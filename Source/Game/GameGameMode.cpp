// Fill out your copyright notice in the Description page of Project Settings.

#include "Game.h"
#include "GameGameMode.h"
#include "Engine.h"

void AGameGameMode::StartPlay() {

	Super::StartPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Game Started"));
	}
}




