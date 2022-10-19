// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_SpreadWeaponComponent.h"

void UTP_SpreadWeaponComponent::Fire()
{
	// TODO Custom Fire for Spread Shots
	UTP_WeaponComponent::Fire();
}
void UTP_SpreadWeaponComponent::SpawnProjectile(UWorld* World)
{
	APlayerController* PlayerController = Cast<APlayerController>(Data.Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(Data.MuzzleOffset);
	const FVector SpawnScale = FVector::One() * SpreadCount;

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the projectile at the muzzle
	AFPRPGProjectile* Projectile = World->SpawnActor<AFPRPGProjectile>(Data.ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	// Temporary spread effect
	Projectile->SetActorRelativeScale3D(SpawnScale);
}