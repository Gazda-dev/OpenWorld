// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class OPENWORLDGAME_API ABird : public APawn
{
	GENERATED_BODY()

public:
	
	ABird();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;
    void MoveForward(float Value);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
    UInputMappingContext* BirdMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
    UInputAction* LookAction;

    void Look(const FInputActionValue& Value);
    void Move(const FInputActionValue& Value);

private:
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* Capsule;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* BirdMesh;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;
    
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;





};
