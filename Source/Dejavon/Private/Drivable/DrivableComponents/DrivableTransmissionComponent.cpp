// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableTransmissionComponent.h"
#include "DrivableConfig/DrivableTransmissionSpecs.h"

UDrivableTransmissionComponent::UDrivableTransmissionComponent() {
	PrimaryComponentTick.bCanEverTick = false;
	CanReverse = true;
	NumberOfGears = 6;
	GearRatios.Append({ 0.0f, 0.3f, 0.5f, 0.72f, 0.85f, 1.0f, 1.3f });
}


// Called when the game starts
void UDrivableTransmissionComponent::BeginPlay() {
	Super::BeginPlay();

	checkf(GearRatios.Num() == (NumberOfGears + 1), TEXT("Number of gears does not match Gear Ratios."));
	checkf(GearRatios[0] == 0.0f, TEXT("First gear ratio must be neutral (eg. 0.0f)."));

	CurrentGear = 0;
}

void UDrivableTransmissionComponent::GearUp() {
	if (CurrentGear < NumberOfGears)
		CurrentGear++;
}

void UDrivableTransmissionComponent::GearDown() {
	if (CanReverse) {
		if (CurrentGear >= 0)
			CurrentGear--;
	} else {
		if (CurrentGear > 0)
			CurrentGear--;
	}
}

void UDrivableTransmissionComponent::SetGear(int32 Gear) {
	if (CanReverse) {
		if (Gear >= -1 && Gear < NumberOfGears && Gear < GearRatios.Num())
			CurrentGear = Gear;
	} else {
		if (Gear >= 0 && Gear < NumberOfGears && Gear < GearRatios.Num())
			CurrentGear = Gear;
	}
}

float UDrivableTransmissionComponent::GetPowerOutput(float EngineOutput) {
	if (CanReverse && CurrentGear == -1 && GearRatios.Num() >= 1) {
		return -(EngineOutput * GearRatios[1]);
	} else if(CurrentGear < GearRatios.Num()){
		return EngineOutput * GearRatios[CurrentGear];
	} else {
		return 0.0f;
	}
}

int32 UDrivableTransmissionComponent::GetCurrentGear() {
	return CurrentGear;
}

void UDrivableTransmissionComponent::SetSpecs(UDrivableTransmissionSpecs* TransmissionSpecs) {
	if (TransmissionSpecs) {
		CanReverse = TransmissionSpecs->CanReverse;
		NumberOfGears = TransmissionSpecs->NumberOfGears;
		GearRatios = TransmissionSpecs->GearRatios;
	} else
		UE_LOG(LogTemp, Warning, TEXT("Transmission Specs not applied (NULL)"));
}