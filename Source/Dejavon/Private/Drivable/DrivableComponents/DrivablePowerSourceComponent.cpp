// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePowerSourceComponent.h"
#include "DrivableConfig/DrivableEngineSpecs.h"

// Sets default values for this component's properties
UDrivablePowerSourceComponent::UDrivablePowerSourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	CurrentRPM = 0;
	Resistance = 0;
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

void UDrivablePowerSourceComponent::OnGearChange(float NewResistance) {
	Resistance = NewResistance;
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
		return -PotentialBraking;
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

void UDrivablePowerSourceComponent::SetSpecs(UDrivableEngineSpecs* EngineSpecs) {
	if (EngineSpecs) {
		MaxRPM = EngineSpecs->MaxRPM;
		IdleRPM = EngineSpecs->IdleRPM;
		Torque = EngineSpecs->Torque;
		RPMPotentialAcceleration = EngineSpecs->RPMPotentialAcceleration;
		PotentialBraking = EngineSpecs->PotentialBraking;
		CurrentRPM = 0;
	} else
		UE_LOG(LogTemp, Warning, TEXT("Engine Specs not applied (NULL)"));
}