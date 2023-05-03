

#include "Characters/SlashCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"


ASlashCharacter::ASlashCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.f;

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View camera"));
    ViewCamera->SetupAttachment(SpringArm);

}


void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MovementMapping, 0);
        }
    }
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
    if (ActionState != EActionState::EAS_Unoccpied) return;

    const FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MovementVector.Y);

    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void ASlashCharacter::Looking(const FInputActionValue& Value)
{
    const FVector2D LookingVector = Value.Get<FVector2D>();
    AddControllerYawInput(LookingVector.X);
    AddControllerPitchInput(LookingVector.Y);
}

void ASlashCharacter::EKeyPressed()
{
    AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
    if (OverlappingWeapon)
    {
        OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
        CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
        OverlappingItem = nullptr;
        EquippedWeapon = OverlappingWeapon;
    }
    else
    {
        if (CanDisarm())
        {
            PlayEquipMontage(FName("Unequip"));
            CharacterState = ECharacterState::ECS_Unequipped;
            ActionState = EActionState::EAS_EquippingWeapon;
        }
        else if (CanArm())
        {
            PlayEquipMontage(FName("Equip"));
            CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
            ActionState = EActionState::EAS_EquippingWeapon;
        }
    }
}

void ASlashCharacter::Attack()
{
    if (CanAttack())
    {
        PlayAttackMontage();
        ActionState = EActionState::EAS_Attacking;
    }
    
}

bool ASlashCharacter::CanAttack()
{
    return ActionState == EActionState::EAS_Unoccpied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanDisarm()
{
    return ActionState == EActionState::EAS_Unoccpied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanArm()
{
    return ActionState == EActionState::EAS_Unoccpied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon;
}


void ASlashCharacter::Dodge()
{
}

void ASlashCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
    if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
    {
        EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
    }
}


void ASlashCharacter::PlayAttackMontage()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && AttackMontage)
    {
        AnimInstance->Montage_Play(AttackMontage);
        const int32 Selection = FMath::RandRange(0, 2);
        FName SectionName = FName();
        switch (Selection)
        {
        case 0:
            SectionName = FName("Attack1");
            break;

        case 1:
            SectionName = FName("Attack2");
            break;

        case 2:
            SectionName = FName("Attack3");
            break;

        default:
            break;
        }
        AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
    }
}

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && EquipMontage)
    {
        AnimInstance->Montage_Play(EquipMontage);
        AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
    }
}

void ASlashCharacter::DisArm()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
    }
}

void ASlashCharacter::Arm()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
    }
}

void ASlashCharacter::FinishEquipping()
{
    ActionState = EActionState::EAS_Unoccpied;
}

void ASlashCharacter::AttackEnd()
{
    ActionState = EActionState::EAS_Unoccpied;
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
        EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Looking);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump);
        EnhancedInputComponent->BindAction(E_Action, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
        EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
    }

}

void ASlashCharacter::Jump()
{
    Super::Jump();
}


