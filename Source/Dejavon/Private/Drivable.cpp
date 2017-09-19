//MIT License Copyright(c) 2017 Nicolas Hamard

#include "Drivable.h"

// Sets default values
ADrivable::ADrivable() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DrivableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrivableMesh"));
	RootComponent = DrivableMesh;

}

// Called when the game starts or when spawned
void ADrivable::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ADrivable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADrivable::MoveForward(float ThrottleInput) {
	UE_LOG(LogTemp, Warning, TEXT("%s : Gas!"), *this->GetFName().ToString());
}

void ADrivable::TurnRight(float SteeringInput) {
	UE_LOG(LogTemp, Warning, TEXT("%s : Durifto!"), *this->GetFName().ToString());
}

void ADrivable::EngageEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("%s : UTurn!"), *this->GetFName().ToString());
}

void ADrivable::ReleaseEBrake() {
	UE_LOG(LogTemp, Warning, TEXT("%s : EndUturn"), *this->GetFName().ToString());
}