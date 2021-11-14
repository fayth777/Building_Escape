// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.h"

#include "UObject/Script.h"

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
	GetPhysicsHandle();
	BindInputActions();
}

FHitResult UGrabber::TraceInFront()
{
	FVector PlayerViewpointLocation;
	FRotator PLayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PLayerViewpointRotation);
	
	// UE_LOG(LogTemp, Log, TEXT("%s"), *PlayerViewpointLocation.ToString());
	// UE_LOG(LogTemp, Log, TEXT("%s"), *PLayerViewpointRotation.ToString());
	FHitResult HitResult;
	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName("RV_Trace"), false, GetOwner());
	RV_TraceParams.bReturnPhysicalMaterial = false;
	RV_TraceParams.TraceTag = TraceTag;
	FVector TraceEnd = PlayerViewpointLocation + PLayerViewpointRotation.Vector() * Reach;
	GetWorld()->LineTraceSingleByChannel(HitResult,  PlayerViewpointLocation, TraceEnd, ECC_Visibility, RV_TraceParams );
	UE_LOG(LogTemp, Log, TEXT("%s"), *HitResult.GetActor()->GetFullName());
	return HitResult;
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp,Error,TEXT("Grab Press"));

}
void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp,Error,TEXT("Grab Release"));

}
void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Physics Handle COmponent NullPtr"));
	}	
}

void UGrabber::BindInputActions()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed,this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released,this, &UGrabber::GrabRelease);

	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Getting InputComponent Failed"));
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceInFront();
	
	// ...
}
