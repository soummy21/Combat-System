// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* PawnRef{ TryGetPawnOwner() }; //Direct Initilization 
	
	if (!IsValid(PawnRef)) return;	

	FVector Velocity { PawnRef->GetVelocity() };

	CurrentSpeed = static_cast<float>(Velocity.Length()); //Explicit type convertion
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	IsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) return;

	if (!IsInCombat) return;

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);

}
