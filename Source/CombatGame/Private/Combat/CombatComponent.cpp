// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/MainPlayer.h"

void UCombatComponent::ComboAttack()
{
	//If the character doesn't have enough stamina don't let it attack
	if (CharacterRef->Implements<UMainPlayer>())
	{
		IMainPlayer* IMainPlayerRef = Cast<IMainPlayer>(CharacterRef);
		if (IMainPlayerRef && !IMainPlayerRef->HasEnoughStamina(staminaCost))
			return;
	}

	if (!CanAttack) return;

	
	CanAttack = false;

	//Play the attack animation from the combo montage
	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);
	ComboCounter++;

	int MaxCombo{ AttackAnimations.Num() };
	
	ComboCounter = UKismetMathLibrary::Wrap(ComboCounter, -1, MaxCombo - 1);

	//Broadcast the event saying the attack has been performed
	OnAttackPerformedDelegate.Broadcast(staminaCost);
	
}

void UCombatComponent::HandleResetAttack()
{
	CanAttack = true;
}

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

