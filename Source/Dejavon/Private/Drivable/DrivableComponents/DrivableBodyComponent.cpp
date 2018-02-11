// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBodyComponent.h"
#include "DrivableWheelComponent.h"
#include "Drivable.h"
#include "Engine/StaticMeshSocket.h"


// Sets default values for this component's properties
UDrivableBodyComponent::UDrivableBodyComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ADrivableWheelComponent*> UDrivableBodyComponent::GetDriveWheels() {
	return DriveWheels;
}

TArray<ADrivableWheelComponent*> UDrivableBodyComponent::GetSteeredWheels() {
	return SteeredWheels;
}

TSubclassOf<ADrivableWheelComponent> UDrivableBodyComponent::GetTemplateWheel() {
	return TemplateWheel;
}


// Called when the game starts
void UDrivableBodyComponent::BeginPlay() {
	Super::BeginPlay();
}

void UDrivableBodyComponent::AttachWheel(ADrivableWheelComponent* wheel, FString tag) {
	if (tag.Contains("Steered")) SteeredWheels.Add(wheel);
	if (tag.Contains("Drive")) DriveWheels.Add(wheel);
}

ADrivable* UDrivableBodyComponent::GetDrivableOwner() {
	ADrivable* owner = Cast<ADrivable>(GetOwner());

	if (owner) return owner;
	else return NULL;
}

void UDrivableBodyComponent::ApplyDriveInput(float driveShaftRPM) {
	if (GetDrivableOwner())
		ApplyInput(GetDriveWheels(), GetDrivableOwner()->GetActorForwardVector() * driveShaftRPM);
}

void UDrivableBodyComponent::ApplySteerInput(float steeringInput) {
	if (GetDrivableOwner())
		ApplyInput(GetDriveWheels(), GetDrivableOwner()->GetActorRightVector() * steeringInput);
}

void UDrivableBodyComponent::ApplyInput(TArray<ADrivableWheelComponent*> wheels, FVector vector) {

	if (wheels.Num() > 0) {
		int32 wheelsNum = wheels.Num();

		for (int i = 0; i < wheels.Num(); i++)
			wheels[i]->ApplyInput(vector / wheelsNum);
	}
}

UStaticMeshComponent* UDrivableBodyComponent::GetBodyMesh() {
	return BodyMesh;
}