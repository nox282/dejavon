// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePowerSourceComponent.h"
#include "DrivableConfig/DrivableEngineSpecs.h"

// Sets default values for this component's properties
UDrivablePowerSourceComponent::UDrivablePowerSourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	CurrentRPM = IdleRPM;
	//CurrentTorque = 0.0f;
	CurrentGearRatio = 0.0f;

	TIRE_DIAMETER = 78.74f;
	V_MASS = 500;
}

void UDrivablePowerSourceComponent::OpenThrottle(float ThrottleInput) {
	CurrentTorque = Torque * ThrottleInput - EngineResistance/2;
}
void UDrivablePowerSourceComponent::CloseThrottle() {
	CurrentTorque = - EngineResistance;
}

void UDrivablePowerSourceComponent::OnBrake(float BrakeInput) {

	CurrentTorque = - (Torque * -BrakeInput + EngineResistance);
}

void UDrivablePowerSourceComponent::OnGearChange(float NewGearRatio, float DriveShaftRPM) {
	float rpm = DriveShaftRPM * NewGearRatio;
	CurrentRPM = ApplyRevLimiter(rpm);
}

float UDrivablePowerSourceComponent::GetPowerOutput() {
	return (CurrentTorque * CurrentRPM) / 5252;
}

float UDrivablePowerSourceComponent::GetCurrentRPM() {
	return CurrentRPM;
}


// Called when the game starts
void UDrivablePowerSourceComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UDrivablePowerSourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentRPM = ProcessCurrentRPM(DeltaTime);

}

float UDrivablePowerSourceComponent::ProcessCurrentRPM(float DeltaTime) {
	float rpm = CurrentRPM + (CurrentTorque/V_MASS);
	return ApplyRevLimiter(rpm);
}

void UDrivablePowerSourceComponent::SetSpecs(UDrivableEngineSpecs* EngineSpecs) {
	if (EngineSpecs) {
		MaxRPM = EngineSpecs->MaxRPM;
		IdleRPM = EngineSpecs->IdleRPM;
		Torque = EngineSpecs->Torque;
		EngineResistance = EngineSpecs->EngineResistance;
		CurrentRPM = IdleRPM;
	} else
		UE_LOG(LogTemp, Warning, TEXT("Engine Specs not applied (NULL)"));
}

float UDrivablePowerSourceComponent::ApplyRevLimiter(float RPM) {
	RPM = RPM < IdleRPM ? IdleRPM : RPM;
	RPM = RPM > MaxRPM ? MaxRPM : RPM;
	
	return RPM;
}