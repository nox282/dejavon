// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "DrivableWheelMovementComponent.h"


UDrivableWheelMovementComponent::UDrivableWheelMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	MaxWorldSpeed = 1000.0f;
	StandardFriction = 10.0f;
}

void UDrivableWheelMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("I am a llama, si."));
	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = GetThisFrameMovementVector(DeltaTime);
	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		UE_LOG(LogTemp, Warning, TEXT("Desired movement : %s"), *DesiredMovementThisFrame.ToString());
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

FVector UDrivableWheelMovementComponent::GetThisFrameMovementVector(float DeltaTime) {
	return GetThisFrameMovementVector(DeltaTime, StandardFriction);
}

FVector UDrivableWheelMovementComponent::GetThisFrameMovementVector(float DeltaTime, float Friction) {
	return ConsumeInputVector() * DeltaTime;
}
