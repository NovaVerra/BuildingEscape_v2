// All Rights Reserved Leo Lee 2020

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	OpenDoorAngle = 90.f;
	TargetYaw = GetOwner()->GetActorRotation().Yaw + OpenDoorAngle;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator	CurrentRotation {GetOwner()->GetActorRotation()};
	FRotator	TargetRotation {CurrentRotation.Pitch, TargetYaw, CurrentRotation.Roll};
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	TargetRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, TargetYaw, 0.02f);
	GetOwner()->SetActorRotation(TargetRotation);
}
