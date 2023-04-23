// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGame/DebugMacros.h"
#include "OpenWorldGame/OpenWorldGame.h"


AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
    RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

    int32 AvgInt = Avg<int32>(1, 3);
    UE_LOG(LogTemp, Warning, TEXT("Avg 1 and 3: %d"), AvgInt);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RunningTime += DeltaTime;

}

float AItem::TransformedSin()
{
    return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
    return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}





