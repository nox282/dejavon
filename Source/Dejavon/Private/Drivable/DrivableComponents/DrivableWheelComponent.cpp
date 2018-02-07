// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableWheelComponent.h"
#include "DrivableWheelMovementComponent.h"

#include "ConstructorHelpers.h"

// Sets default values for this component's properties
ADrivableWheelComponent::ADrivableWheelComponent() {
	//PrimaryComponentTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	WheelMovementComponent = NewObject<UDrivableWheelMovementComponent>();

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelMesh"));
	RootComponent = BodyMesh;
	BodyMesh->SetCollisionProfileName(TEXT("UI"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> wheelVisual(TEXT("/Game/Meshes/Mesh_wheel"));
	if (wheelVisual.Succeeded())
		BodyMesh->SetStaticMesh(wheelVisual.Object);
}


UDrivableWheelMovementComponent * ADrivableWheelComponent::GetWheelMovementComponent() {
	return WheelMovementComponent;
}

// Called when the game starts
void ADrivableWheelComponent::BeginPlay() {
	Super::BeginPlay();
}

UStaticMeshComponent* ADrivableWheelComponent::GetBodyMesh() {
	return BodyMesh;
}

FName ADrivableWheelComponent::GetSocketName() {
	return SocketName;
}

void ADrivableWheelComponent::SetSocketName(FName name) {
	SocketName = name;
}