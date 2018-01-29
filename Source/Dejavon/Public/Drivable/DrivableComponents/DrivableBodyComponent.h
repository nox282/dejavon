// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableBodyComponent.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class DEJAVON_API UDrivableBodyComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UDrivableBodyComponent();
		UDrivableBodyComponent(int32 DriveWheelsCount, int32 SteeredWheelsCount);

		virtual TArray<class UDrivableWheelComponent*> GetDriveWheels();
		virtual TArray<UDrivableWheelComponent*> GetSteeredWheels();

		//virtual void ApplyVector(FVector Vector);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent")
			int32 DriveCount;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent")
			int32 SteeredCount;

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
			TArray<UDrivableWheelComponent*> DriveWheels;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
			TArray<UDrivableWheelComponent*> SteeredWheels;
};
