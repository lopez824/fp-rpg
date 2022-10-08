// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TP_WeaponComponent.h"
#include "FPRPGCharacter.h"
#include "FPRPGProjectile.h"
#include "TP_SpreadWeaponComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPRPG_API UTP_SpreadWeaponComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpreadOptions)
		int32 SpreadCount;

protected:
	virtual void Fire() override;
	virtual void SpawnProjectile(UWorld* World) override;
};
