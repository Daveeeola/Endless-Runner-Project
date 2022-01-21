// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void URunAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(!Pawn)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		MovementComponent = Pawn->GetMovementComponent();
	}
}


void URunAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn  && MovementComponent)
	{
		bIsInAir = MovementComponent->IsFalling();
		speed = Pawn->GetVelocity().Size();
	}
	
}
