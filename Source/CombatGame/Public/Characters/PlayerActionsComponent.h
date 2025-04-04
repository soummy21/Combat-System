// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature, 
	UPlayerActionsComponent, 
	OnSprintDelegate, 
	float, 
	StaminaCost
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATGAME_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* CharacterRef;
	class IMainPlayer* MainPlayerInterfaceRef;
	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere)
	float sprintCost{ 0.1f };
	UPROPERTY(EditAnywhere)
	float sprintSpeed{ 1000.0f };
	UPROPERTY(EditAnywhere)
	float walkSpeed{ 600.0f };

public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();
	
	UFUNCTION(BlueprintCallable)
	void Walk();

};
