// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePowerSourceComponent.h"
#include "DrivableConfig/DrivableEngineSpecs.h"

// Sets default values for this component's properties
UDrivablePowerSourceComponent::UDrivablePowerSourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	CurrentRPM = IdleRPM;
	CurrentTorque = 0.0f;
	CurrentGearRatio = 0.0f;
	V_MASS = 500;
	EngineResistanceFactor = 3.0f;
}

void UDrivablePowerSourceComponent::OpenThrottle(float ThrottleInput) {
	CurrentTorque = TC(ThrottleInput, CurrentRPM);
}
void UDrivablePowerSourceComponent::CloseThrottle() {
	CurrentTorque = - TC(1.0f, CurrentRPM) / EngineResistanceFactor;
}

void UDrivablePowerSourceComponent::OnBrake(float BrakeInput) {
	if (CurrentRPM >= MaxRPM * 0.25f)
		CurrentTorque = - TC(BrakeInput, CurrentRPM);
	else 
		CurrentTorque = -TC(BrakeInput, MaxRPM * 0.25f);
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

	UE_LOG(LogTemp, Warning, TEXT("Current EngineRPM : %f"), CurrentRPM);
	UE_LOG(LogTemp, Warning, TEXT("Current Torque : %f"), CurrentTorque);

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

		EngineResistanceFactor = EngineSpecs->EngineResistanceFactor;
		if (EngineResistanceFactor == 0) 
			EngineResistanceFactor = 3.0f;

		V_MASS = EngineSpecs->V_MASS;
		if (V_MASS == 0)
			V_MASS = 500.0f;

		CurrentRPM = IdleRPM;

		TC = TorqueCurve(MaxRPM, Torque);
	} else
		UE_LOG(LogTemp, Warning, TEXT("Engine Specs not applied (NULL)"));
}

float UDrivablePowerSourceComponent::ApplyRevLimiter(float RPM) {
	RPM = RPM < IdleRPM ? IdleRPM : RPM;
	RPM = RPM > MaxRPM ? MaxRPM : RPM;
	
	return RPM;
}