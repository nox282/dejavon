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
	virtual void OnGearChange(float NewResistance);

	virtual float GetPowerOutput();
	
	virtual void SetSpecs(class UDrivableEngineSpecs* EngineSpecs);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int32 MaxRPM;
	int32 IdleRPM;
	int32 Torque;
	int32 RPMPotentialAcceleration;
	int32 PotentialBraking;
	
	int32 CurrentRPM;
	int32 RPMCurrentAcceleration;
	float Resistance;

	int32 ProcessRPMCurrentAcceleration();
	int32 ProcessCurrentRPM(int32 ThisFrameRPMAcceleration);
};
