// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "OpenWorldGame/DebugMacros.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemy::AEnemy()
{

	PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(true);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::PlayHitReactMonatge(const FName& SectionName)
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && HitReactMontage)
    {
        AnimInstance->Montage_Play(HitReactMontage);
        AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
    }

}

void AEnemy::GetHit(const FVector& ImpactPoint)
{
    DRAW_SPHERE2(ImpactPoint);

    directionalHitReact(ImpactPoint);
}

void AEnemy::directionalHitReact(const FVector& ImpactPoint)
{

    const FVector Forward = GetActorForwardVector();

    const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);        //lower impact point to the enemy actor location z
    const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

 
    const double CosTheta = FVector::DotProduct(Forward, ToHit);                            // Forward * ToHit = |Forward||ToHit| * cos (theta)
                                                                                            // |Forward? = 1, |ToHit| = 1, so Forward * ToHit = cos(theta)
 
    double Theta = FMath::Acos(CosTheta);                                                   //Take the inverse cosine (arc-cosine) of cos(theta) to get theta
    Theta = FMath::RadiansToDegrees(Theta);

    const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);                     //if CrossProduct points down, Theta should be negative
    if (CrossProduct.Z < 0)
    {
        Theta *= -1.f;
    }

    FName Section = FName("FromBack");

    if (Theta >= -45.f && Theta < 45.f)
    {
        Section = FName("FromFront");
    }
    else if (Theta < -45.f && Theta >= -135.f)
    {
        Section = FName("FromLeft");
    }
    else if (Theta >= 45.f && Theta < 135.f)
    {
        Section = FName("FromRight");
    }

    PlayHitReactMonatge(Section);
    UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 100.f, 5.f, FColor::Blue, 5.f);


    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Theta: %f"), Theta));
    }
    UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 60.f, 5.f, FColor::Red, 5.f);
    UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f, FColor::Green, 5.f);
}

