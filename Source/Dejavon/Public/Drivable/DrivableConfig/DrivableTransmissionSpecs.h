// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableTransmissionSpecs.generated.h"


UCLASS(ClassGroup = (DrivableComponent), Blueprintable, meta = (BlueprintSpawnableComponent))
class DEJAVON_API UDrivableTransmissionSpecs : public UActorComponent {
	GENERATED_BODY()
	
	public:
		// Sets default values for this component's properties
		UDrivableTransmissionSpecs();

		// Called when the game starts
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableTransmissionComponent")
		bool CanReverse;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableTransmissionComponent")
		int32 NumberOfGears;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableTransmissionComponent")
		TArray<float> GearRatios;
};
