// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableTransmissionComponent.generated.h"


UCLASS( ClassGroup=(DrivableComponent), meta=(BlueprintSpawnableComponent) )
class DEJAVON_API UDrivableTransmissionComponent : public UActorComponent {
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UDrivableTransmissionComponent();

		virtual void GearUp();
		virtual void GearDown();
		virtual void SetGear(int32 Gear);

		virtual float GetDriveshaftRPM(float EngineRPM);

		UFUNCTION(BlueprintCallable, category = "DrivableTransmissionComponent")
		virtual int32 GetCurrentGear();

		UFUNCTION(BlueprintCallable, category = "DrivableTransmissionComponent")
		virtual float GetCurrentGearRatio();

		virtual void SetSpecs(class UDrivableTransmissionSpecs* TransmissionSpecs);

	protected:
		virtual void BeginPlay() override;

	private:		
		bool CanReverse;
		int32 NumberOfGears;
		TArray<float> GearRatios;

		int32 CurrentGear;
};
