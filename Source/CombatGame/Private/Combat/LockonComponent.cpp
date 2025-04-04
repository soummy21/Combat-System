// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "Interfaces/Enemy.h"

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	ControllerRef = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
	
}

void ULockonComponent::StartLockon(float radius)
{	
	FHitResult OutResult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(radius) };
	FCollisionQueryParams IgnoreParams{
		FName { TEXT("Ignore Collision Parameters")},
		false,
		OwnerRef
	};

	//Check if there is a target within the radius of the projected sphere
	bool hasFoundTarget = GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnoreParams
		);

	if (!hasFoundTarget) return;

	if (!OutResult.GetActor()->Implements<UEnemy>()) return;
	
	//Lock on to the target by setting the current actor's rotation looking at the target
	CurrentTargetActor = OutResult.GetActor();
	ControllerRef->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;

	SpringArmComp->TargetOffset = FVector{ 0.0, 0.0, 100.0 };

	IEnemy::Execute_OnSelect(CurrentTargetActor);
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	//UE_LOG(LogTemp, Warning, TEXT("Current Target Name: %s"), *CurrentTargetActor->GetName());
	if(CurrentTargetActor->Implements<UEnemy>())	
		IEnemy::Execute_OnDeselect(CurrentTargetActor);

	//Reset the current actor
	CurrentTargetActor = nullptr;
	ControllerRef->ResetIgnoreLookInput();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;

	SpringArmComp->TargetOffset = FVector::ZeroVector;
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
		EndLockon();
	else
		StartLockon(Radius);
}


// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Player does not have a current target
	if (!IsValid(CurrentTargetActor)) return;

	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FVector TargetLocation{ CurrentTargetActor->GetActorLocation() };

	double PlayerDistanceToTarget{ FVector::Distance(CurrentLocation, TargetLocation) };

	//If the player is too far from the target, end the lockon
	if (PlayerDistanceToTarget > BreakDistance)
	{
		EndLockon();
		return;

	}

	TargetLocation.Z -= 125;
	FRotator LookAtRotaion{ UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation) };

	ControllerRef->SetControlRotation(LookAtRotaion);



}

