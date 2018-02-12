// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableWheelComponent.h"
#include "DrivableWheelMovementComponent.h"

#include "ConstructorHelpers.h"

// Sets default values for this component's properties
ADrivableWheelComponent::ADrivableWheelComponent() {
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelMesh"));
	RootComponent = BodyMesh;
	BodyMesh->SetCollisionProfileName(TEXT("UI"));	// Change that someday.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> wheelVisual(TEXT("/Game/Meshes/Mesh_wheel"));
	if (wheelVisual.Succeeded())
		BodyMesh->SetStaticMesh(wheelVisual.Object);

	// Actors can not have PawnMovementCoponents
	WheelMovementComponent = NewObject<UDrivableWheelMovementComponent>(this, TEXT("WheelMovement"));
	if (GetWheelMovementComponent())
		GetWheelMovementComponent()->UpdatedComponent = this->GetRootComponent();
}

void ADrivableWheelComponent::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UDrivableWheelMovementComponent* ADrivableWheelComponent::GetWheelMovementComponent() {
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

void ADrivableWheelComponent::ApplyInput(FVector vector) {
	if (GetWheelMovementComponent())
		GetWheelMovementComponent()->AddInputVector(vector);
}