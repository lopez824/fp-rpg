// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "FPRPGCharacter.h"
#include "FPRPGProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UTP_WeaponComponent::Fire()
{
	if(Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr && AmmoDisplay != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (AmmoDisplay->CurrentAmmoCount > 0)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// Spawn the projectile at the muzzle
				World->SpawnActor<AFPRPGProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

				AmmoDisplay->DecreaseAmmoCount();

				// Try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
				}

				// Try and play a firing animation if specified
				if (FireAnimation != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
			}
			else
			{
				if (EmptySound != nullptr)
					UGameplayStatics::PlaySoundAtLocation(this, EmptySound, Character->GetActorLocation());
			}
		}
	}
}

void UTP_WeaponComponent::Reload()
{
	if (AmmoDisplay != nullptr)
	{
		if (ReloadSound != nullptr)
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, Character->GetActorLocation());
		AmmoDisplay->Reload();
	}
		
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
		Character->OnReload.RemoveDynamic(this, &UTP_WeaponComponent::Reload);
	}
}

void UTP_WeaponComponent::AttachWeapon(AFPRPGCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if(Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);

		// Registers to reload event
		Character->OnReload.AddDynamic(this, &UTP_WeaponComponent::Reload);

		// Get this weapon's ammo component
		AmmoDisplay = Cast<UTP_AmmoComponent>(GetOwner()->GetComponentByClass(UTP_AmmoComponent::StaticClass()));
	}
}

