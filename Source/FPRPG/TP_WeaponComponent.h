// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GunData.h"
#include "TP_WeaponComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPRPG_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPRPGCharacter* TargetCharacter);

protected:
	// Struct for data shared amongst guns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FGunData Data;

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	// Spawns bullet
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void SpawnProjectile(UWorld* World);

	// Play the sound if specified
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlaySound(USoundBase* Sound);

	// Play a firing animation if specified
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlayAnimation(UAnimMontage* Animation);

	/** Reload weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
