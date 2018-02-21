// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableBehaviorsComponent.generated.h"


UCLASS( ClassGroup = (DrivableComponent), Blueprintable, meta = (BlueprintSpawnableComponent) )
class DEJAVON_API UDrivableBehaviorsComponent : public UActorComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UDrivableBehaviorsComponent();

	virtual class ADrivable* GetDrivableOwner();

	virtual void SetEngineSpecs(class UDrivableEngineSpecs* EngineSpecs);
	virtual void SetTransmissionSpecs(class UDrivableTransmissionSpecs* TransmissionSpecs);

	virtual float GetPowerDelivery();

	virtual void Gas(float ThrottleInput);
	virtual void Brake(float BrakeInput);
	virtual void EngineBrake();
	virtual void AddSteeringLock(float SteeringInput);
	virtual void PullEbrake();
	virtual void ReleaseEBrake();
	virtual void ShiftUp();
	virtual void ShiftDown();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual class UDrivablePowerSourceComponent* GetEngine();
	virtual class UDrivableTransmissionComponent* GetTransmission();

	virtual class UDrivableSteeringWheelComponent* GetSteeringWheelComponent();

	virtual void ShiftGear(void (UDrivableTransmissionComponent::*ShiftFunction)());

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
	class UDrivablePowerSourceComponent* Engine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
	class UDrivableTransmissionComponent* Transmission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
	class UDrivableSteeringWheelComponent* SteeringWheel;
};
