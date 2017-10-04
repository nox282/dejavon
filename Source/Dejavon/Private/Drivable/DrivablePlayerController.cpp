// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivablePlayerController.h"
#include "GameModes/TrackAttackMode.h"
#include "Drivable.h"

ADrivablePlayerController::ADrivablePlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void ADrivablePlayerController::BeginPlay() {
	Super::BeginPlay();
	takeControlOfLinkedDrivable();
}

void ADrivablePlayerController::takeControlOf(TSubclassOf<ADrivable> drivable) {
	SetDrivable(drivable);
	takeControlOfLinkedDrivable();
}

void ADrivablePlayerController::takeControlOfLinkedDrivable() {
	if (!GetDrivable()) return;
	
	FVector vec(-205.0, 0, 124.008842);

	APawn* newPawn = GetWorld()->SpawnActor<ADrivable>(GetDrivable()->GetDefaultObject()->GetClass(), vec, FRotator::ZeroRotator);
	
	if (newPawn) 
		this->Possess(newPawn);

}

void ADrivablePlayerController::SetDrivable(TSubclassOf<ADrivable> drivable) {
	if (!GetDrivable()) {
		linkedDrivable = drivable;
	}
	else {
		//stuff to do when drivable isn't null
		this->UnPossess();
		linkedDrivable = drivable;
	}
}

TSubclassOf<class ADrivable> ADrivablePlayerController::GetDrivable() {
	return linkedDrivable;
}

void ADrivablePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADrivablePlayerController::MoveForward);
	InputComponent->BindAxis("TurnRight", this, &ADrivablePlayerController::TurnRight);
	InputComponent->BindAction("EBrake", IE_Pressed, this, &ADrivablePlayerController::EngageEBrake);
	InputComponent->BindAction("EBrake", IE_Released, this, &ADrivablePlayerController::ReleaseEBrake);
	InputComponent->BindAction("ShiftUp", IE_Pressed, this, &ADrivablePlayerController::ShiftUp);
	InputComponent->BindAction("ShiftDown", IE_Pressed, this, &ADrivablePlayerController::ShiftDown);
}

void ADrivablePlayerController::MoveForward(float ThrottleInput) {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->MoveForward(ThrottleInput);
	}
}

void ADrivablePlayerController::TurnRight(float SteeringInput) {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->TurnRight(SteeringInput);
	}
}

void ADrivablePlayerController::EngageEBrake() {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->EngageEBrake();
	}
}

void ADrivablePlayerController::ReleaseEBrake() {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->ReleaseEBrake();
	}
}

void ADrivablePlayerController::ShiftUp() {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->ShiftUp();
	}
}

void ADrivablePlayerController::ShiftDown() {
	ADrivable* pawn = Cast<ADrivable>(this->GetPawn());
	if (pawn) {
		pawn->ShiftDown();
	}
}