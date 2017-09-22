//MIT License Copyright(c) 2017 Nicolas Hamard

#include "Drivable.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrivableMovementComponent.h"

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

	DrivableMovement = CreateDefaultSubobject<UDrivableMovementComponent>(TEXT("DrivableMovement"));
	GetMovementComponent()->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ADrivable::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("I'm moving : %s"), *this->GetActorLocation().ToString());
}

// Called every frame
void ADrivable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UPawnMovementComponent* ADrivable::GetMovementComponent() const {
	return DrivableMovement;
}

void ADrivable::MoveForward(float ThrottleInput) {
	if (GetMovementComponent() && (GetMovementComponent()->UpdatedComponent == RootComponent)) {
		if (ThrottleInput >= 0)
			GetMovementComponent()->AddInputVector(GetActorForwardVector() * ThrottleInput* Horsepower);
		else
			GetMovementComponent()->AddInputVector(GetActorForwardVector() * ThrottleInput* (Brakepower));
	}
}

void ADrivable::TurnRight(float SteeringInput) {
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += SteeringInput;
	SetActorRotation(NewRotation);
}

void ADrivable::EngageEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("Engaging EBrake"));
}

void ADrivable::ReleaseEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("Disengaging EBrake"));
}