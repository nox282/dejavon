// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivablePowerSourceComponent.generated.h"

UCLASS( ClassGroup = (DrivableComponent), Blueprintable, meta = (BlueprintSpawnableComponent) )
class DEJAVON_API UDrivablePowerSourceComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDrivablePowerSourceComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void OpenThrottle(float ThrottleInput);
	virtual void CloseThrottle();

	virtual void OnBrake(float BrakeInput);
	virtual void OnGearChange(float NewResistance, float DriveShaftRPM);


	virtual float GetPowerOutput();
	virtual float GetCurrentRPM();
	
	virtual void SetSpecs(class UDrivableEngineSpecs* EngineSpecs);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float TIRE_DIAMETER;
	float V_MASS;

	float MaxRPM;
	float IdleRPM;
	float Torque;
	float EngineResistance;
	
	float CurrentTorque;
	float CurrentGearRatio;

	float CurrentRPM;
	
	//int32 RPMCurrentAcceleration;
	
	float ProcessCurrentRPM(float DeltaTime);
	float ApplyRevLimiter(float RPM);
};
