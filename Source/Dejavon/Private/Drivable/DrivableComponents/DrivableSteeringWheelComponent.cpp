// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableSteeringWheelComponent.h"


// Sets default values for this component's properties
UDrivableSteeringWheelComponent::UDrivableSteeringWheelComponent() {
	PrimaryComponentTick.bCanEverTick = false;

	SteeringInput = 0.0f;
}


float UDrivableSteeringWheelComponent::GetSteeringInput() {
	return SteeringInput;
}

void UDrivableSteeringWheelComponent::SetSteeringInput(float input) {
	SteeringInput = input;
}

// Called when the game starts
void UDrivableSteeringWheelComponent::BeginPlay() {
	Super::BeginPlay();	
}
