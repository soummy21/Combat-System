// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStats.h"
#include "StatsComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATGAME_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double RegenerateStaminaRate{ 10.0 };

	UPROPERTY(VisibleAnywhere) // Can't modify in the editor, just for debugging
	bool CanRegen { true };

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration{ 5.0f };

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float amount);
	
	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float amount);

	UFUNCTION(BlueprintCallable)
	void RegenerateStamina();

	UFUNCTION()
	void EnableRegeneration();
		
};
