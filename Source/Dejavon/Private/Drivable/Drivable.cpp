//MIT License Copyright(c) 2017 Nicolas Hamard

#include "Drivable.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrivableBehaviorsComponent.h"
#include "DrivableConfig/DrivableEngineSpecs.h"
#include "DrivableConfig/DrivableTransmissionSpecs.h"

// Sets default values
ADrivable::ADrivable() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DrivableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrivableMesh"));
	RootComponent = DrivableMesh;
	DrivableMesh->SetCollisionProfileName(TEXT("Pawn"));


	// Use a spring arm to give the camera smooth, natural-feeling motion.
	DrivableSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("DrivableCameraAttachmentArm"));
	DrivableSpringArm->SetupAttachment(RootComponent);
	DrivableSpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	DrivableSpringArm->TargetArmLength = 400.0f;
	DrivableSpringArm->bEnableCameraLag = true;
	DrivableSpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	DrivableCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DrivableCamera"));
	DrivableCamera->SetupAttachment(DrivableSpringArm, USpringArmComponent::SocketName);
}

void ADrivable::HandleDrivableSpecs() {
	UDrivableEngineSpecs* engineSpecs = this->FindComponentByClass<UDrivableEngineSpecs>();
	if (engineSpecs && GetBehaviorsComponent())
		GetBehaviorsComponent()->SetEngineSpecs(engineSpecs);

	UDrivableTransmissionSpecs* transmissionSpecs = this->FindComponentByClass<UDrivableTransmissionSpecs>();
	if (engineSpecs && GetBehaviorsComponent())
		GetBehaviorsComponent()->SetTransmissionSpecs(transmissionSpecs);
}

// Called when the game starts or when spawned
void ADrivable::BeginPlay() {
	Super::BeginPlay();
	DrivableBehaviors = NewObject<UDrivableBehaviorsComponent>(this, TEXT("DrivableBehaviors"));
	DrivableBehaviors->RegisterComponent();
	
	if (DrivableBehaviors)
		HandleDrivableSpecs();
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