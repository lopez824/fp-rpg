// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_AmmoComponent.h"
#include "GunData.generated.h"

class AFPRPGCharacter;

USTRUCT(BlueprintType)
struct FPRPG_API FGunData
{
	GENERATED_BODY()

	/** The Character holding this weapon*/
	AFPRPGCharacter* Character;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPRPGProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** Sound to play with an empty clip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* EmptySound;

	/** Sound to play when reloading */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ReloadSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun Fire Rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Ammo Display
	UPROPERTY(BlueprintReadWrite)
	UTP_AmmoComponent* AmmoDisplay;

	void SetMuzzleOffset(FVector Vector)
	{
		MuzzleOffset = Vector;
	}
};
