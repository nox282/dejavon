// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableEngineSpecs.generated.h"


UCLASS(ClassGroup = (DrivableComponent), Blueprintable, meta = (BlueprintSpawnableComponent))
class DEJAVON_API UDrivableEngineSpecs : public UActorComponent {
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UDrivableEngineSpecs();

		// Called when the game starts
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent")
		int32 MaxRPM;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent")
		int32 IdleRPM;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent")
		int32 Torque;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent")
		int32 RPMPotentialAcceleration;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivablePowerSourceComponent")
		int32 PotentialBraking;
};
