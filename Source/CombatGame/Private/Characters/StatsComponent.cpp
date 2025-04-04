// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StatsComponent.h"
#include "Characters/EStats.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ReduceHealth(float amount)
{
	Stats[EStats::Health] -= amount;
	Stats[EStats::Health] = 
		UKismetMathLibrary::FClamp(
			Stats[EStats::Health], 
			0.0f, Stats[EStats::MaxHealth]
		);
	
}

void UStatsComponent::ReduceStamina(float amount)
{
	Stats[EStats::Stamina] -= amount;
	Stats[EStats::Stamina] = 
		UKismetMathLibrary::FClamp(
			Stats[EStats::Stamina], 
			0.0f, Stats[EStats::MaxStamina]
		);

	CanRegen = false;

	
	FLatentActionInfo FuncInfo
	{
		0,
		100, 
		TEXT("EnableRegeneration"),
		this
	};

	//Delay to enable regen
	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(), 
		StaminaDelayDuration , 
		FuncInfo);
}

void UStatsComponent::RegenerateStamina()
{
	if (!CanRegen) return;

	Stats[EStats::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStats::Stamina], 
		Stats[EStats::MaxStamina], 
		GetWorld()->DeltaTimeSeconds,
		RegenerateStaminaRate
	);
}

void UStatsComponent::EnableRegeneration()
{
	CanRegen = true;
}

