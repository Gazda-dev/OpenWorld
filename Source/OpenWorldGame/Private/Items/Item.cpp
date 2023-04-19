// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGame/DebugMacros.h"
#include "OpenWorldGame/OpenWorldGame.h"


AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RunningTime += DeltaTime;
    float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
    AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
    
    DRAW_SPHERE_SINGLEFRAME(GetActorLocation());
    DRAW_VECTOR_SINGLEFRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

