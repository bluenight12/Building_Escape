// Copyright KDG 2021

#include "OpenDoor.h"

#include "GameFrameWork/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UOpenDoor::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    FRotator OpenDoor(0.f, 0.f, 0.f);
    //생성자에서 GetOwner 사용 X Null값 반환할 수도 있음
    OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 20);
    GetOwner()->SetActorRotation(OpenDoor);
}
