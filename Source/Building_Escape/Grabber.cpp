// Copyright KDG 2021

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay() {
    Super::BeginPlay();

    FindPhysicsHandle();
    SetupInputComponent();
}

void UGrabber::SetupInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}

// Checking for Physics handle component
void UGrabber::FindPhysicsHandle() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle) {
    } else {
        UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

    GetFirstPhysicsBodyInReach();

    // if we hit something then attach the physics handle.
    // TODO attach physics handle
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));
    //TODO remove/release the physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // If the physics handle is attach
    // Move the object we are holding.
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
    // Get players Viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation);

    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; // 본인의 위치벡터에 로테이션을 벡터 변환 * 거리를 더해줌

    FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams);

    AActor *ActorHit = Hit.GetActor();
    if (ActorHit) {
        UE_LOG(LogTemp, Warning, TEXT("Line trace has hit : %s"), *(ActorHit->GetName()));
    }

    return Hit;
}