// All Rights Reserved Leo Lee 2020

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

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
	OpenAngle += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate is set - nullptr undefined error"),
		*GetOwner()->GetName())
	}

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenVelocity);
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 1.f);
	FRotator	TargetRotation {GetOwner()->GetActorRotation()};
	TargetRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(TargetRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseVelocity);
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 1.f);
	FRotator	TargetRotation {GetOwner()->GetActorRotation()};
	TargetRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(TargetRotation);
}
