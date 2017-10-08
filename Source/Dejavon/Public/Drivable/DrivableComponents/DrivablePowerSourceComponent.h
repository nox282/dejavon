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

	struct TorqueCurve {
		/* RPM : x axis bounds */
		float XMax;
		/* Torque : y axis bounds */
		float YMax;

		float EngineMaxRPM, EngineMaxTorque;

		TorqueCurve() : XMax(6.5f), YMax(10.0f) {
			EngineMaxRPM = 0.0f;
			EngineMaxTorque = 0.0f;
		};

		TorqueCurve(float _EngineMaxRPM, float _EngineMaxTorque) : XMax(6.5f), YMax(10.0f) {
			EngineMaxRPM = _EngineMaxRPM;
			EngineMaxTorque = _EngineMaxTorque;
		};

		/* Torque function : f(x) = ((-2x^2 + 20x) / 5) with 0 <= x <= 6.5 */
		virtual float operator() (float ThrottleInput, float RPM) const {
			if (EngineMaxRPM == 0.0f || YMax == 0.0f) return 0.0f;

			float x = (XMax * RPM) / EngineMaxRPM;
			float y = ((-2 * (x*x) + 20 * x) / 5);
			return (EngineMaxTorque * y) / YMax;
		}
	};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float TIRE_DIAMETER;
	float V_MASS;

	float MaxRPM;
	float IdleRPM;
	float Torque;
	float EngineResistanceFactor;
	
	float CurrentTorque;
	float CurrentGearRatio;

	float CurrentRPM;
		
	float ProcessCurrentRPM(float DeltaTime);
	float ApplyRevLimiter(float RPM);

	TorqueCurve TC;
};
