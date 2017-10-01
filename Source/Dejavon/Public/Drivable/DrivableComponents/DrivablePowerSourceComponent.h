// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivablePowerSourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEJAVON_API UDrivablePowerSourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDrivablePowerSourceComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void OpenThrottle(float ThrottleInput);
	virtual void CloseThrottle();
	virtual void OnBrake(float BrakeInput);

	virtual float GetPowerOutput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent", Meta = (BlueprintProtected = "true"))
	int32 MaxRPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent", Meta = (BlueprintProtected = "true"))
	int32 IdleRPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent", Meta = (BlueprintProtected = "true"))
	int32 Torque;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent", Meta = (BlueprintProtected = "true"))
	int32 RPMPotentialAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent", Meta = (BlueprintProtected = "true"))
	int32 PotentionBraking;

private:
	int32 CurrentRPM;
	int32 RPMCurrentAcceleration;

	int32 ProcessRPMCurrentAcceleration();
	int32 ProcessCurrentRPM(int32 ThisFrameRPMAcceleration);
};
