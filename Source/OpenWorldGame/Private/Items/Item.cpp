// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "OpenWorldGame/OpenWorldGame.h"

#define THIRTY 30


AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Cyan, FString("GEngine"));
	}

	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	DRAW_SPHERE(Location);
	

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
	
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);
		FString Name = GetName();
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Cyan, Message);
		GEngine->AddOnScreenDebugMessage(2, 30.f, FColor::Cyan, *Name);

	}
}

