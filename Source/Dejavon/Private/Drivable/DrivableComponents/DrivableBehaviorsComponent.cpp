// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableBehaviorsComponent.h"
#include "DrivableMovementComponent.h"
#include "DrivablePowerSourceComponent.h"
#include "DrivableTransmissionComponent.h"
#include "Drivable.h"


// Sets default values for this component's properties
UDrivableBehaviorsComponent::UDrivableBehaviorsComponent() {
	PrimaryComponentTick.bCanEverTick = true;
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

	MovementComponent = NewObject<UDrivableMovementComponent>(this, TEXT("Movement"));
	MovementComponent->RegisterComponent();
	if (GetDrivableOwner())
		MovementComponent->UpdatedComponent = GetDrivableOwner()->GetRootComponent();
	else
		UE_LOG(LogTemp, Warning, TEXT("No owner"));

	Engine = NewObject<UDrivablePowerSourceComponent>(this, TEXT("Engine"));
	Engine->RegisterComponent();

	Transmission = NewObject<UDrivableTransmissionComponent>(this, TEXT("Transmission"));
	Transmission->RegisterComponent();
}


// Called every frame
void UDrivableBehaviorsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	float engineOutput = GetEngine()->GetPowerOutput();
	//UE_LOG(LogTemp, Warning, TEXT("%f"), engineOutput);

	if (GetMovementComponent() 
			&& GetDrivableOwner()
			&& GetTransmission()
			&& (GetMovementComponent()->UpdatedComponent == GetDrivableOwner()->GetRootComponent())) {
		GetMovementComponent()->AddInputVector(GetDrivableOwner()->GetActorForwardVector() * GetTransmission()->GetPowerOutput(engineOutput));
	}
}

ADrivable* UDrivableBehaviorsComponent::GetDrivableOwner() {
	ADrivable* owner = Cast<ADrivable>(GetOwner());
	
	if (owner) return owner;
	else return NULL;
}

UDrivableMovementComponent* UDrivableBehaviorsComponent::GetMovementComponent() {
	return MovementComponent;
}

UDrivablePowerSourceComponent* UDrivableBehaviorsComponent::GetEngine() {
	return Engine;
}

UDrivableTransmissionComponent* UDrivableBehaviorsComponent::GetTransmission() {
	return Transmission;
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

void UDrivableBehaviorsComponent::AddSteeringLock(float SteeringInput){
	FRotator NewRotation = GetDrivableOwner()->GetActorRotation();
	NewRotation.Yaw += SteeringInput;
	GetDrivableOwner()->SetActorRotation(NewRotation);
}
void UDrivableBehaviorsComponent::PullEbrake(){
	Brake(1);
}
void UDrivableBehaviorsComponent::ReleaseEBrake(){
	EngineBrake();
}

void UDrivableBehaviorsComponent::ShiftUp() {
	if (GetTransmission())
		GetTransmission()->GearUp();
}

void UDrivableBehaviorsComponent::ShiftDown() {
	if (GetTransmission())
		GetTransmission()->GearDown();
}