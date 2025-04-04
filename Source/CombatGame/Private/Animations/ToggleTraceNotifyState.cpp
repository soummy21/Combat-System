// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ToggleTraceNotifyState.h"
#include "Combat/TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UpdateTraceAttackBool(MeshComp, true);
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UpdateTraceAttackBool(MeshComp, false);
}

void UToggleTraceNotifyState::UpdateTraceAttackBool(USkeletalMeshComponent* MeshComp, const bool IsAttacking)
{
	UTraceComponent* TraceComponent{ MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>()
	};

	if (!IsValid(TraceComponent)) return;

	TraceComponent->IsAttacking = IsAttacking;
}

