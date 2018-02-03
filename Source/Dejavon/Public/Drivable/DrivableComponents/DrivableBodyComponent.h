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
		//(int32 DriveWheelsCount, int32 SteeredWheelsCount);

		virtual TArray<class UDrivableWheelComponent*> GetDriveWheels();
		virtual TArray<class UDrivableWheelComponent*> GetSteeredWheels();
		virtual UStaticMeshComponent* GetBodyMesh();

		//virtual void ApplyVector(FVector Vector);
		
		/** 
		  *Instantiate and attach wheels to the BodyMesh sockets 
		  *	returns the new body mesh (with wheels)
		  * arguments : wheelReference - The wheels that will be attached
		*/
		virtual UStaticMeshComponent* AttachWheels(class UDrivableWheelComponent* wheelReference);

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

		virtual void SetDriveWheels(class UDrivableWheelComponent* wheels);
		virtual void SetSteeredWheels(class UDrivableWheelComponent* wheels);

	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BodyMesh;

		TArray<class UDrivableWheelComponent*> DriveWheels;
		TArray<class UDrivableWheelComponent*> SteeredWheels;
};
