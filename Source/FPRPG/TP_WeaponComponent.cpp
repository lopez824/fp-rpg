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
	FVector Offset = FVector(100.0f, 0.0f, 10.0f);
	Data.SetMuzzleOffset(Offset);
}

void UTP_WeaponComponent::Fire()
{
	if(Data.Character == nullptr || Data.Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (Data.ProjectileClass != nullptr && Data.AmmoDisplay != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (Data.AmmoDisplay->CurrentAmmoCount > 0)
			{
				SpawnProjectile(World);
				Data.AmmoDisplay->DecreaseAmmoCount();
				PlaySound(Data.FireSound);
				PlayAnimation(Data.FireAnimation);
			}
			else
			{
				PlaySound(Data.EmptySound);
			}
		}
	}
}

void UTP_WeaponComponent::SpawnProjectile(UWorld* World)
{
	APlayerController* PlayerController = Cast<APlayerController>(Data.Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(Data.MuzzleOffset);

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the projectile at the muzzle
	World->SpawnActor<AFPRPGProjectile>(Data.ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}

void UTP_WeaponComponent::PlayAnimation(UAnimMontage* Animation)
{
	if (Animation != nullptr)
	{
		UAnimInstance* AnimInstance = Data.Character->GetMesh1P()->GetAnimInstance();

		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Animation, 1.f);
	}
}

void UTP_WeaponComponent::PlaySound(USoundBase* Sound)
{
	if (Sound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Data.Character->GetActorLocation());
}

void UTP_WeaponComponent::Reload()
{
	if (Data.AmmoDisplay != nullptr)
	{
		if (Data.AmmoDisplay->CurrentAmmoCount != Data.AmmoDisplay->ClipSize)
		{
			if (Data.ReloadSound != nullptr)
				UGameplayStatics::PlaySoundAtLocation(this, Data.ReloadSound, Data.Character->GetActorLocation());
			Data.AmmoDisplay->Reload();
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Data.Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Data.Character->OnAttack.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
		Data.Character->OnReload.RemoveDynamic(this, &UTP_WeaponComponent::Reload);
	}
}

void UTP_WeaponComponent::AttachWeapon(AFPRPGCharacter* TargetCharacter)
{
	Data.Character = TargetCharacter;
	if(Data.Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Data.Character->GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

		// Map Fire Rate to Character Attack Speed
		Data.Character->SetAttackSpeed(Data.FireRate);

		// Register so that Fire is called every time the character tries to use the item being held
		Data.Character->OnAttack.AddDynamic(this, &UTP_WeaponComponent::Fire);

		// Registers to reload event
		Data.Character->OnReload.AddDynamic(this, &UTP_WeaponComponent::Reload);

		// Get this weapon's ammo component
		Data.AmmoDisplay = Cast<UTP_AmmoComponent>(GetOwner()->GetComponentByClass(UTP_AmmoComponent::StaticClass()));
	}
}

