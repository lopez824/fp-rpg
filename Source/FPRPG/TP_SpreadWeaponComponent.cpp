// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_SpreadWeaponComponent.h"

void UTP_SpreadWeaponComponent::Fire()
{
	// TODO Custom Fire for Spread Shots
	UTP_WeaponComponent::Fire();
}
void UTP_SpreadWeaponComponent::SpawnProjectile(UWorld* World)
{
	// TODO Custom Spawn for Spread Shots
	UTP_WeaponComponent::SpawnProjectile(World);
}