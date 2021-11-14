// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}



// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	TargetRotation = GetOwner()->GetActorRotation();
	TargetRotation.Yaw += TargetYawRotation;
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);

	}
	else
	{
		CloseDoor(DeltaTime);
	}

	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 2);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentRotation = FMath::RInterpTo(CurrentRotation, StartRotation, DeltaTime, 2);
	GetOwner()->SetActorRotation(CurrentRotation);
}