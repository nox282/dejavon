// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableWheelComponent.h"
#include "DrivableWheelMovementComponent.h"


// Sets default values for this component's properties
UDrivableWheelComponent::UDrivableWheelComponent() {
	PrimaryComponentTick.bCanEverTick = false;

	WheelMovementComponent = NewObject<UDrivableWheelMovementComponent>();
}


UDrivableWheelMovementComponent * UDrivableWheelComponent::GetWheelMovementComponent() {
	return WheelMovementComponent;
}

// Called when the game starts
void UDrivableWheelComponent::BeginPlay() {
	Super::BeginPlay();
}

UStaticMeshComponent* UDrivableWheelComponent::GetBodyMesh() {
	return BodyMesh;
}

FName UDrivableWheelComponent::GetSocketName() {
	return SocketName;
}