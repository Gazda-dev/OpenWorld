// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "OpenWorldGame/DebugMacros.h"
#include "OpenWorldGame/OpenWorldGame.h"
#include "Components/SphereComponent.h"


AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
    RootComponent = ItemMesh;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    Sphere->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
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

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const FString OtherActorName = OtherActor->GetName();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
    }
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Green, TEXT("End overlapping"));
    }
}





