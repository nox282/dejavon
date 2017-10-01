// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePowerSourceComponent.h"

// Sets default values for this component's properties
UDrivablePowerSourceComponent::UDrivablePowerSourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	CurrentRPM = 0;
	
	MaxRPM = 8000;
	IdleRPM = 500;
	Torque = 200;
	RPMPotentialAcceleration = 20;
	PotentionBraking = 7;
}

void UDrivablePowerSourceComponent::OpenThrottle(float ThrottleInput) {
	RPMCurrentAcceleration = FMath::RoundHalfFromZero(RPMPotentialAcceleration * ThrottleInput);
}
void UDrivablePowerSourceComponent::CloseThrottle() {
	RPMCurrentAcceleration = 0;
}

void UDrivablePowerSourceComponent::OnBrake(float BrakeInput) {
	RPMCurrentAcceleration = FMath::RoundHalfFromZero(RPMPotentialAcceleration * BrakeInput);
}

float UDrivablePowerSourceComponent::GetPowerOutput() {
	return (Torque * CurrentRPM) / 5252;
}

// Called when the game starts
void UDrivablePowerSourceComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UDrivablePowerSourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	int32 ThisFrameRPMAcceleration = ProcessRPMCurrentAcceleration();
	CurrentRPM = ProcessCurrentRPM(ThisFrameRPMAcceleration);
}

int32 UDrivablePowerSourceComponent::ProcessRPMCurrentAcceleration() {
	if (RPMCurrentAcceleration == 0)
		return -PotentionBraking;
	else
		return RPMCurrentAcceleration;
}

int32 UDrivablePowerSourceComponent::ProcessCurrentRPM(int32 ThisFrameRPMAcceleration) {
	float rpm = CurrentRPM;

	rpm += ThisFrameRPMAcceleration;

	rpm = rpm < 0 ? 0 : rpm;
	rpm = rpm > MaxRPM ? MaxRPM : rpm;

	return rpm;
}