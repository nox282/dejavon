// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePlayerController.h"
#include "GameModes/TrackAttackMode.h"

ADrivablePlayerController::ADrivablePlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

/*void ADrivablePlayerController::Tick(float DeltaTime) {
	//Super::Tick(DeltaTime);
}*/


void ADrivablePlayerController::BeginPlay() {
	Super::BeginPlay();

	ATrackAttackMode* gameMode = Cast<ATrackAttackMode>(GetWorld()->GetAuthGameMode());
	SetDrivable(Cast<ADrivable>(gameMode->DefaultPawnClass.GetDefaultObject()));
}

void ADrivablePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("setting up player input..."));
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADrivablePlayerController::MoveForward);
	InputComponent->BindAxis("TurnRight", this, &ADrivablePlayerController::TurnRight);
	InputComponent->BindAction("EBrake", IE_Pressed, this, &ADrivablePlayerController::EngageEBrake);
	InputComponent->BindAction("EBrake", IE_Released, this, &ADrivablePlayerController::ReleaseEBrake);
	UE_LOG(LogTemp, Warning, TEXT("setting up player input...DONE"));
}

void ADrivablePlayerController::MoveForward(float ThrottleInput) {
	if(ThrottleInput != 0)
		UE_LOG(LogTemp, Warning, TEXT("Player controller calling MoveForward();"));
	if(linkedDrivable != NULL)
		linkedDrivable->MoveForward(ThrottleInput);
}

void ADrivablePlayerController::TurnRight(float SteeringInput) {
	if (SteeringInput != 0)
		UE_LOG(LogTemp, Warning, TEXT("Player controller calling TurnRight();"));
	if (linkedDrivable != NULL)
		linkedDrivable->TurnRight(SteeringInput);
}

void ADrivablePlayerController::EngageEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("Player controller calling EngageEBrake();"));
	if (linkedDrivable != NULL)
		linkedDrivable->EngageEBrake();
}

void ADrivablePlayerController::ReleaseEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("Player controller calling ReleaseEBrake();"));
	if (linkedDrivable != NULL)
		linkedDrivable->ReleaseEBrake();
}