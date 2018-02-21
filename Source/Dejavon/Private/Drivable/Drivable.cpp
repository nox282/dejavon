//MIT License Copyright(c) 2017 Nicolas Hamard

#include "Drivable.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMeshSocket.h"

#include "DrivableBehaviorsComponent.h"
#include "DrivableBodyComponent.h"
#include "DrivableWheelComponent.h"

#include "DrivableConfig/DrivableEngineSpecs.h"
#include "DrivableConfig/DrivableTransmissionSpecs.h"

// Sets default values
ADrivable::ADrivable() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADrivable::HandleDrivableSpecs() {
	UDrivableEngineSpecs* engineSpecs = this->FindComponentByClass<UDrivableEngineSpecs>();
	if (engineSpecs && GetBehaviorsComponent())
		GetBehaviorsComponent()->SetEngineSpecs(engineSpecs);

	UDrivableTransmissionSpecs* transmissionSpecs = this->FindComponentByClass<UDrivableTransmissionSpecs>();
	if (transmissionSpecs && GetBehaviorsComponent())
		GetBehaviorsComponent()->SetTransmissionSpecs(transmissionSpecs);
}

void ADrivable::HandleBodyComponent() {
	DrivableMesh = this->FindComponentByClass<UStaticMeshComponent>();
	if (GetDrivableMesh()) {
		TArray<UStaticMeshSocket*> sockets = GetDrivableMesh()->GetStaticMesh()->Sockets;
		for (int i = 0; i < sockets.Num(); i++) {
			FTransform t = GetDrivableMesh()->GetSocketTransform(sockets[i]->SocketName, ERelativeTransformSpace::RTS_Actor);
			UE_LOG(LogTemp, Warning, TEXT("Socket Position : %s"), *t.ToString());
			if (sockets[i]->Tag.Contains("Steered")) SteeredWheels.Add(t);
			if (sockets[i]->Tag.Contains("Drive")) DriveWheels.Add(t);
		}
	}
}

// Called when the game starts or when spawned
void ADrivable::BeginPlay() {
	Super::BeginPlay();
	DrivableBehaviors = NewObject<UDrivableBehaviorsComponent>(this, TEXT("DrivableBehaviors"));
	DrivableBehaviors->RegisterComponent();
	
	if (DrivableBehaviors)
		HandleDrivableSpecs();
	
	HandleBodyComponent();
}

// Called every frame
void ADrivable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UDrivableBehaviorsComponent* ADrivable::GetBehaviorsComponent() const {
	return DrivableBehaviors;
}

void ADrivable::MoveForward(float ThrottleInput) {
	if (GetBehaviorsComponent()) {

		if (ThrottleInput > 0)
			GetBehaviorsComponent()->Gas(ThrottleInput);
		else if (ThrottleInput < 0)
			GetBehaviorsComponent()->Brake(ThrottleInput);
		else
			GetBehaviorsComponent()->EngineBrake();
	}
}

void ADrivable::TurnRight(float SteeringInput) {
	if (GetBehaviorsComponent())
		GetBehaviorsComponent()->AddSteeringLock(SteeringInput);
}

void ADrivable::EngageEBrake() {
	if (GetBehaviorsComponent())
		GetBehaviorsComponent()->PullEbrake();
}

void ADrivable::ReleaseEBrake() {
	if (GetBehaviorsComponent())
		GetBehaviorsComponent()->ReleaseEBrake();
}

void ADrivable::ShiftUp() {
	if (GetBehaviorsComponent())
		GetBehaviorsComponent()->ShiftUp();
}

void ADrivable::ShiftDown() {
	if (GetBehaviorsComponent())
		GetBehaviorsComponent()->ShiftDown();
}