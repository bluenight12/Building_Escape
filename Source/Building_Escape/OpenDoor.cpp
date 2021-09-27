// Copyright KDG 2021

#include "OpenDoor.h"

#include "GameFrameWork/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UOpenDoor::BeginPlay() {
    Super::BeginPlay();
    InitialYaw = GetOwner()->GetActorRotation().Yaw;
    CurrentYaw = InitialYaw;
    TargetYaw += InitialYaw;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoor(DeltaTime);
    }
}

void UOpenDoor::OpenDoor(float DeltaTime) {
    CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 0.5f);
    FRotator DoorRotation = GetOwner()->GetActorRotation();
    DoorRotation.Yaw = CurrentYaw;
    GetOwner()->SetActorRotation(DoorRotation);
}