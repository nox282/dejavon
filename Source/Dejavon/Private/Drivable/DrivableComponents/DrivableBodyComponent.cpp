// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBodyComponent.h"
#include "DrivableWheelComponent.h"
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

void UDrivableBodyComponent::AttachWheels(ADrivableWheelComponent* wheel, FString tag) {
	if (tag.Contains("Steered")) SteeredWheels.Add(wheel);
	if (tag.Contains("Drive")) DriveWheels.Add(wheel);
}

UStaticMeshComponent* UDrivableBodyComponent::GetBodyMesh() {
	return BodyMesh;
}