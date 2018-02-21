// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBehaviorsComponent.h"
#include "DrivablePowerSourceComponent.h"
#include "DrivableTransmissionComponent.h"
#include "DrivableSteeringWheelComponent.h"
#include "Drivable.h"


// Sets default values for this component's properties
UDrivableBehaviorsComponent::UDrivableBehaviorsComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UDrivableBehaviorsComponent::SetEngineSpecs(UDrivableEngineSpecs* EngineSpecs) {
	if (GetEngine())
		GetEngine()->SetSpecs(EngineSpecs);
}

void UDrivableBehaviorsComponent::SetTransmissionSpecs(UDrivableTransmissionSpecs* TransmissionSpecs) {
	if (GetTransmission())
		GetTransmission()->SetSpecs(TransmissionSpecs);
}

// Called when the game starts
void UDrivableBehaviorsComponent::BeginPlay() {
	Super::BeginPlay();

	Engine = NewObject<UDrivablePowerSourceComponent>(this, TEXT("Engine"));
	Engine->RegisterComponent();

	Transmission = NewObject<UDrivableTransmissionComponent>(this, TEXT("Transmission"));
	Transmission->RegisterComponent();

	SteeringWheel = NewObject<UDrivableSteeringWheelComponent>(this, TEXT("Steering Wheel"));
	SteeringWheel->RegisterComponent();
}

ADrivable* UDrivableBehaviorsComponent::GetDrivableOwner() {
	ADrivable* owner = Cast<ADrivable>(GetOwner());
	
	if (owner) return owner;
	else return NULL;
}

UDrivablePowerSourceComponent* UDrivableBehaviorsComponent::GetEngine() {
	return Engine;
}

UDrivableTransmissionComponent* UDrivableBehaviorsComponent::GetTransmission() {
	return Transmission;
}

UDrivableSteeringWheelComponent * UDrivableBehaviorsComponent::GetSteeringWheelComponent() {
	return SteeringWheel;
}

float UDrivableBehaviorsComponent::GetPowerDelivery() {
	if (GetTransmission() && GetEngine())
		return GetTransmission()->GetDriveshaftRPM(GetEngine()->GetCurrentRPM());
	else
		return 0.0f;
}

void UDrivableBehaviorsComponent::Gas(float ThrottleInput) {
	if (GetEngine())
		GetEngine()->OpenThrottle(ThrottleInput);
}

void UDrivableBehaviorsComponent::Brake(float BrakeInput) {
	if (GetEngine())
		GetEngine()->OnBrake(BrakeInput);
}

void UDrivableBehaviorsComponent::EngineBrake() {
	if (GetEngine())
		GetEngine()->CloseThrottle();
}

void UDrivableBehaviorsComponent::AddSteeringLock(float SteeringInput) {
	if (GetSteeringWheelComponent())
		GetSteeringWheelComponent()->SetSteeringInput(SteeringInput);
}

void UDrivableBehaviorsComponent::PullEbrake() {
	Brake(1);
}

void UDrivableBehaviorsComponent::ReleaseEBrake() {
	EngineBrake();
} 

void UDrivableBehaviorsComponent::ShiftUp() {
	ShiftGear(&UDrivableTransmissionComponent::GearUp);
}

void UDrivableBehaviorsComponent::ShiftDown() {
	ShiftGear(&UDrivableTransmissionComponent::GearDown);
}

void UDrivableBehaviorsComponent::ShiftGear(void (UDrivableTransmissionComponent::*ShiftFunction)()) {
	if (GetTransmission() && GetEngine()) {
		int32 previousGear = GetTransmission()->GetCurrentGear();
		float driveShaftRPM = GetTransmission()->GetDriveshaftRPM(GetEngine()->GetCurrentRPM());
		(GetTransmission()->*ShiftFunction)();
		float gearRatio = GetTransmission()->GetCurrentGearRatio();

		if (previousGear != 0)
			GetEngine()->OnGearChange(gearRatio, driveShaftRPM);
	}
}