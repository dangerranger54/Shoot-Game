// Fill out your copyright notice in the Description page of Project Settings.

#include "Game.h"
#include "MainCharacter.h"
#include "Engine.h"
#include "Projectile.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent1st = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent1st->AttachTo(GetCapsuleComponent());

	CameraComponent1st->SetRelativeLocation(FVector(0.0f, 0.0f, 50.f + BaseEyeHeight));
	CameraComponent1st->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player started"));
	}
	
}

// Called every frame
void AMainCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::EndJump);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::EndSprint);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);

}

void AMainCharacter::MoveForward(float Value) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	
	
	
	if (bIsSprinting) {
		Value *= 2;
	}

	AddMovementInput(Direction, Value / 2);
	
}

void AMainCharacter::MoveRight(float Value) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value / 2);
}

void AMainCharacter::StartJump() {
	bPressedJump = true;
}

void AMainCharacter::EndJump() {
	bPressedJump = false;
}

void AMainCharacter::StartSprint() {
	bIsSprinting = true;
}

void AMainCharacter::EndSprint() {
	bIsSprinting = false;
}

void AMainCharacter::Fire() {

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("Fire Started")));
	if (ProjectileClass) {

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("Zone 1 Clear")));

		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();

		if (World) {

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("Zone 2 Clear")));

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile) {

				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("Fire Sent")));

				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}

		
	}
}

