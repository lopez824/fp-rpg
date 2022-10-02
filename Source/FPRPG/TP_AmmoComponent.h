// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "TP_AmmoComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPRPG_API UTP_AmmoComponent : public UTextRenderComponent
{
	GENERATED_BODY()

public:

	// Maximum ammo count for gun
	UPROPERTY(EditAnywhere, Category = AmmoDetails)
	int32 ClipSize;

	// Displayed ammo count for gun
	UPROPERTY(BlueprintReadOnly, Category = AmmoDetails)
	int32 CurrentAmmoCount;

	UTP_AmmoComponent();

	// Called when gun is fired
	UFUNCTION(BlueprintCallable)
	void DecreaseAmmoCount();

	// Called when gun is reloaded
	UFUNCTION(BlueprintCallable)
	void Reload();

private:
	// Helper function for Int - String - FText conversions
	FText TextFromInt(int32 value);
};
