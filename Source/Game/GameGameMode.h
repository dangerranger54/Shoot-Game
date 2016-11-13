// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AGameGameMode : public AGameMode
{
	GENERATED_BODY()

		virtual void StartPlay() override;
	
	
	
};
