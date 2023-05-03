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
class UAnimMontage;
class AWeapon;

UCLASS()
class OPENWORLDGAME_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void Jump() override;

    UFUNCTION(BlueprintCallable)
    void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

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

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* AttackAction;

    UPROPERTY(EditAnywhere, Category = "Input_cpp")
    UInputAction* DodgeAction;

    /*
    * Callbacks for input
    */

    void Move(const FInputActionValue& Value);
    void Looking(const FInputActionValue& Value);
    void EKeyPressed();
    void Attack();
    void Dodge();

    /*
    * Play montage functions
    */

    void PlayAttackMontage();

    UFUNCTION(BlueprintCallable)
    void AttackEnd();
    bool CanAttack();

    bool CanDisarm();
    bool CanArm();
    void PlayEquipMontage(FName SectionName);

    UFUNCTION(BlueprintCallable)
    void DisArm();

    UFUNCTION(BlueprintCallable)
    void Arm();

    UFUNCTION(BlueprintCallable)
    void FinishEquipping();

private:

    ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EActionState ActionState = EActionState::EAS_Unoccpied;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleInstanceOnly)
    AItem* OverlappingItem;

    UPROPERTY(VisibleAnywhere, Category = Weapon_cpp)
    AWeapon* EquippedWeapon;

    /*
    * Animation montages
    */

    UPROPERTY(EditDefaultsOnly, Category = Montages_cpp)
    UAnimMontage* AttackMontage;

    UPROPERTY(EditDefaultsOnly, Category = Montages_cpp)
    UAnimMontage* EquipMontage;

public:

    FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
    FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
