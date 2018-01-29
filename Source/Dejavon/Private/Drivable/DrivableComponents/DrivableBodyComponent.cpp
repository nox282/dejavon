// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBodyComponent.h"
#include "DrivableWheelComponent.h"


// Sets default values for this component's properties
UDrivableBodyComponent::UDrivableBodyComponent() {
	PrimaryComponentTick.bCanEverTick = false;

	DriveCount = 2;
	SteeredCount = 2;
}

UDrivableBodyComponent::UDrivableBodyComponent(int32 DriveWheelsCount, int32 SteeredWheelsCount) {
	PrimaryComponentTick.bCanEverTick = false;
	
	DriveCount = DriveWheelsCount;
	SteeredCount = SteeredWheelsCount;
}

TArray<class UDrivableWheelComponent*> UDrivableBodyComponent::GetDriveWheels() {
	return DriveWheels;
}

TArray<UDrivableWheelComponent*> UDrivableBodyComponent::GetSteeredWheels() {
	return SteeredWheels;
}

// Called when the game starts
void UDrivableBodyComponent::BeginPlay() {
	Super::BeginPlay();

	for (int32 d = 0; d < DriveCount; d++)
		DriveWheels.Add(NewObject<UDrivableWheelComponent>());

	for (int32 s = 0; s < SteeredCount; s++)
		SteeredWheels.Add(NewObject<UDrivableWheelComponent>());
}
