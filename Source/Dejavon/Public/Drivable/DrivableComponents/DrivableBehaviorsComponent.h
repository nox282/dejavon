// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableBehaviorsComponent.generated.h"


UCLASS()
class DEJAVON_API UDrivableBehaviorsComponent : public UActorComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UDrivableBehaviorsComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual class ADrivable* GetDrivableOwner();

	virtual void Gas(float ThrottleInput);
	virtual void Brake(float BrakeInput);
	virtual void EngineBrake();
	virtual void AddSteeringLock(float SteeringInput);
	virtual void PullEbrake();
	virtual void ReleaseEBrake();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual class UDrivableMovementComponent* GetMovementComponent();
	virtual class UDrivablePowerSourceComponent* GetEngine();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
	class UDrivableMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
	class UDrivablePowerSourceComponent* Engine;
};
