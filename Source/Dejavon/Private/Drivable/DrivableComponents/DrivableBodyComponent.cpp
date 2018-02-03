// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBodyComponent.h"
#include "DrivableWheelComponent.h"
#include "Engine/StaticMeshSocket.h"


// Sets default values for this component's properties
UDrivableBodyComponent::UDrivableBodyComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

/*UDrivableBodyComponent::UDrivableBodyComponent(int32 DriveWheelsCount, int32 SteeredWheelsCount) {
	PrimaryComponentTick.bCanEverTick = false;
	
	DriveCount = DriveWheelsCount;
	SteeredCount = SteeredWheelsCount;
}*/

TArray<class UDrivableWheelComponent*> UDrivableBodyComponent::GetDriveWheels() {
	return DriveWheels;
}

TArray<UDrivableWheelComponent*> UDrivableBodyComponent::GetSteeredWheels() {
	return SteeredWheels;
}

// Called when the game starts
void UDrivableBodyComponent::BeginPlay() {
	Super::BeginPlay();
}

UStaticMeshComponent* UDrivableBodyComponent::AttachWheels(UDrivableWheelComponent* wheel) {
	if (!GetBodyMesh()) return nullptr;
	
	bool isAttached;
	if (wheel && wheel->GetBodyMesh())
		isAttached = wheel->GetBodyMesh()->AttachToComponent(GetBodyMesh(), FAttachmentTransformRules::KeepWorldTransform, wheel->GetSocketName());
	
	if (isAttached) return GetBodyMesh();
	else return nullptr;
}

void UDrivableBodyComponent::SetDriveWheels(class UDrivableWheelComponent* wheels) {

}

void UDrivableBodyComponent::SetSteeredWheels(class UDrivableWheelComponent* wheels) {

}

UStaticMeshComponent* UDrivableBodyComponent::GetBodyMesh() {
	return BodyMesh;
}