// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_AmmoComponent.h"

UTP_AmmoComponent::UTP_AmmoComponent()
{
	// Setup Text Render Component properties
	FVector locationOffset = FVector(0.f, 5.25f, 19.7f);
	FRotator rotationOffset = FRotator(0.f, -90.f, 0.f);
	this->SetRelativeLocation(locationOffset);
	this->SetRelativeRotation(rotationOffset);
	this->SetHorizontalAlignment(EHTA_Center);
	this->SetVerticalAlignment(EVRTA_TextCenter);
	this->SetWorldSize(3.0f);
}

FText UTP_AmmoComponent::TextFromInt(int32 value)
{
	FString string = FString::FromInt(value);
	return FText::FromString(string);
}

void UTP_AmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Text
	CurrentAmmoCount = ClipSize;
	FText ammoText = TextFromInt(CurrentAmmoCount);
	this->SetText(ammoText);
}

void UTP_AmmoComponent::DecreaseAmmoCount()
{
	CurrentAmmoCount = CurrentAmmoCount - 1;
	if (CurrentAmmoCount < 0)
		CurrentAmmoCount = 0;

	FText ammoText = TextFromInt(CurrentAmmoCount);
	this->SetText(ammoText);
}

void UTP_AmmoComponent::Reload()
{
	int32 ammoOnReload = CurrentAmmoCount;
	CurrentAmmoCount = ClipSize;
	FText ammoText = TextFromInt(CurrentAmmoCount);
	this->SetText(ammoText);
}