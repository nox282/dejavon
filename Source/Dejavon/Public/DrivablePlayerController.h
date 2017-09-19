// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Drivable.h"
#include "DrivablePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEJAVON_API ADrivablePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		ADrivablePlayerController();
		
		FORCEINLINE ADrivable* GetDrivable() { return linkedDrivable; }
		FORCEINLINE void SetDrivable(ADrivable* drivable) {
			if (linkedDrivable == NULL)
				linkedDrivable = drivable;
		}
		
	protected:
		/** Binds this controller to the instance of current default pawn */
		virtual void BeginPlay() override;

		//virtual void Tick(float DeltaTime) override;

		/** Setup Binding between Inputs and Drivable */
		virtual void SetupInputComponent() override;


	private:
		ADrivable* linkedDrivable;

		void MoveForward(float ThrottleInput);
		void TurnRight(float SteeringInput);
		void EngageEBrake();
		void ReleaseEBrake();
};