// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class AItem;

UCLASS()
class OPENWORLDGAME_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void Jump() override;

protected:
	
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputMappingContext* MovementMapping;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* MovementAction;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* LookingAction;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* E_Action;

    void Move(const FInputActionValue& Value);
    void Looking(const FInputActionValue& Value);
    void EKeyPressed();

private:

    ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleInstanceOnly)
    AItem* OverlappingItem;

public:

    FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
    FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
