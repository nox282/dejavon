// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableBodyComponent.generated.h"


UCLASS(ClassGroup = (DrivableComponent), Blueprintable, meta = (BlueprintSpawnableComponent))
class DEJAVON_API UDrivableBodyComponent : public UActorComponent {
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UDrivableBodyComponent();
		
		virtual TArray<class ADrivableWheelComponent*> GetDriveWheels();
		virtual TArray<class ADrivableWheelComponent*> GetSteeredWheels();
		virtual UStaticMeshComponent* GetBodyMesh();
		virtual TSubclassOf<class ADrivableWheelComponent> GetTemplateWheel();
		
		// Populates DriveWheels and SteeredWheels arrays
		virtual void AttachWheel(class ADrivableWheelComponent* wheelReference, FString tag);

		virtual class ADrivable* GetDrivableOwner();

		virtual void ApplyDriveInput(float driveShaftRPM);
		virtual void ApplySteerInput(float steeringInput);

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BodyMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ADrivableWheelComponent> TemplateWheel;

		TArray<class ADrivableWheelComponent*> DriveWheels;
		TArray<class ADrivableWheelComponent*> SteeredWheels;

		void ApplyInput(TArray<class ADrivableWheelComponent*> wheels, FVector vector);
};
