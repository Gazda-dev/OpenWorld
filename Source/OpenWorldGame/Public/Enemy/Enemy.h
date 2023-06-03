// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

class UAnimMontage;

UCLASS()
class OPENWORLDGAME_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void GetHit(const FVector& ImpactPoint) override;
    void directionalHitReact(const FVector& ImpactPoint);
public:

	AEnemy();

private:

    /*
    * Animation montages
    */

    UPROPERTY(EditDefaultsOnly, Category = Montages_cpp)
    UAnimMontage* HitReactMontage;

protected:

	virtual void BeginPlay() override;

    /*
    * Play montage functions
    */
    
    void PlayHitReactMonatge(const FName& SectionName);



};
