// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableWheelMovementComponent.h"


UDrivableWheelMovementComponent::UDrivableWheelMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UDrivableWheelMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
}
