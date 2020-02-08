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
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.f);
	FRotator	TargetRotation {GetOwner()->GetActorRotation()};
	TargetRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(TargetRotation);
	// TargetRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 2.f);
	// TargetRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, TargetYaw, 1.2f * DeltaTime);
}
