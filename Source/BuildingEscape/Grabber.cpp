// All Rights Reserved Leo Lee 2020

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is here"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector		PlayerViewPointLocation {};
	FRotator	PlayerViewPointDirection {};

	// Get Player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointDirection
	);

	// Log both location and direction
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *PlayerViewPointLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *PlayerViewPointDirection.ToString());

	// Ray-cast out to a certain distance

	// What are we hitting?
}
