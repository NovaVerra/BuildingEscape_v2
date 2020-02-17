// All Rights Reserved Leo Lee 2020

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void	UOpenDoor::BeginPlay()
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
}

// Called every frame
void	UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	if (GetTotalMass() > TotalMassToOpenDoor)
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

void	UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenVelocity);
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 1.f);
	FRotator	TargetRotation {GetOwner()->GetActorRotation()};
	TargetRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(TargetRotation);
}

void	UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseVelocity);
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 1.f);
	FRotator	TargetRotation {GetOwner()->GetActorRotation()};
	TargetRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(TargetRotation);
}

float	UOpenDoor::GetTotalMass()
{
	TotalMassOfActors = 0.f;
	// Find overlapping actors
	TArray<AActor*>	OverlappingActors {};
	if (!PressurePlate) { return TotalMassOfActors; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Add up masses
	for (AActor *Actor : OverlappingActors)
	{
		TotalMassOfActors += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate"), *Actor->GetName());
	}
	return TotalMassOfActors;
}
