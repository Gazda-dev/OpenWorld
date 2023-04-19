// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class OPENWORLDGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Params")
    float Amplitude = 0.25f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Params")
    float TimeConstant = 5.f;

	virtual void BeginPlay() override;
private:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sine Params", meta = (AllowPrivateAccess = "true"))
    float RunningTime;
	

};
