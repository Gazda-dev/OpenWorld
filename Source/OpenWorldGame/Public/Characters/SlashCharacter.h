// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class OPENWORLDGAME_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputMappingContext* MovementMapping;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* MovementAction;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* LookingAction;

    void Move(const FInputActionValue& Value);
    void Looking(const FInputActionValue& Value);

private:
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;
};
