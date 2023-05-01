// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

enum class EItemState : uint8
{
    EIS_Hovering,
    EIS_Equipped
};

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

    UFUNCTION(BlueprintPure)
    float TransformedSin();

    UFUNCTION(BlueprintPure)
    float TransformedCos();

    template<typename T>
    T Avg(T First, T Second);

    UFUNCTION()
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* ItemMesh;

    EItemState ItemState = EItemState::EIS_Hovering;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* Sphere;

private:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sine Params", meta = (AllowPrivateAccess = "true"))
    float RunningTime;
};

template<typename T>
inline T AItem::Avg(T First, T Second)
{
    return (First + Second)/2;
}


