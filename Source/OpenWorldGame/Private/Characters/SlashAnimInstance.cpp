// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
    if (SlashCharacter)
    {
        SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
    }
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);
}
