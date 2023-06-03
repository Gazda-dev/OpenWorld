// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Characters/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HitInterface.h"

AWeapon::AWeapon()
{
    WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
    WeaponBox->SetupAttachment(GetRootComponent());
    WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

    BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
    BoxTraceStart->SetupAttachment(GetRootComponent());

    BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
    BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();

    WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
    AttachMeshToSocket(InParent, InSocketName);
    ItemState = EItemState::EIS_Equipped;
    if (EquipSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            EquipSound,
            GetActorLocation()
        );
    }
    if (Sphere)
    {
        Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
    FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
    ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                              bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

// The AWeapon::OnBoxOverlap function is invoked when a collision or "overlap" event is detected. 
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // This section is determining the start and end points of a box trace in the game world. The box trace is a method of 
    // checking what lies between these two points.
    // BoxTraceStart and BoxTraceEnd are probably references to components within the weapon actor.
    const FVector Start = BoxTraceStart->GetComponentLocation();  // The start point of the trace.
    const FVector End = BoxTraceEnd->GetComponentLocation();  // The end point of the trace.

    // ActorsToIgnore is an array of actors that the trace will intentionally overlook.
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);  // Adding the current instance (this weapon) to the ignore list.

    // This loop adds actors to the ignore list from another list named IgnoreActos. 
    // IgnoreActos might be a misspelling. It might supposed to be IgnoreActors.
    for (AActor* Actor : IgnoreActos)  // For each actor in the IgnoreActos list.
    {
        ActorsToIgnore.AddUnique(Actor);  // Add the actor to the ignore list if it's not already there.
    }

    // BoxHit will hold the result of the trace, including what was hit, where, and at what angle.
    FHitResult BoxHit;

    // BoxTraceSingle performs the trace operation from the Start to the End position with the specified dimensions and parameters.
    UKismetSystemLibrary::BoxTraceSingle(
        this,  // The world context.
        Start,  // The start position of the trace.
        End,  // The end position of the trace.
        FVector(2.5f, 2.5f, 2.5f),  // The dimensions of the box being traced.
        BoxTraceStart->GetComponentRotation(),  // The orientation of the box.
        ETraceTypeQuery::TraceTypeQuery1,  // The type of objects to trace.
        false,  // Whether to trace complex (as opposed to simple) objects.
        ActorsToIgnore,  // The actors to ignore during the trace.
        EDrawDebugTrace::ForDuration,  // Debug: draws the trace for a certain duration.
        BoxHit,  // The output hit result.
        true  // Whether to ignore self (this weapon) in the trace.
    );

    // If the trace hit an actor, the hit actor will be returned. 
    // If no actor was hit, it will return null.
    if (BoxHit.GetActor())  // If the trace hit an actor.
    {
        // Cast the hit actor to an interface type IHitInterface. If the actor doesn't implement this interface, it will return null.
        IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
        if (HitInterface)  // If the hit actor implements the IHitInterface.
        {
            // Call the GetHit method of the hit actor's interface with the point of impact as an argument.
            HitInterface->GetHit(BoxHit.ImpactPoint);
        }
        // Adds the hit actor to the IgnoreActos list so that it will be ignored in future traces.
        IgnoreActos.AddUnique(BoxHit.GetActor());
    }
}

