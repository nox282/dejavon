// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrivablePlayerController.generated.h"

UCLASS()
class DEJAVON_API ADrivablePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		ADrivablePlayerController();
		
		//FORCEINLINE class ADrivable* GetDrivable() { return linkedDrivable; }
		
		UFUNCTION(BlueprintCallable, category = "Drivable Controller")
		void SetDrivable(TSubclassOf<class ADrivable> drivable);

		UFUNCTION(BlueprintCallable, category = "Drivable Controller")
		TSubclassOf<class ADrivable> GetDrivable();
	protected:

		
		/** Binds this controller to the instance of current default pawn */
		virtual void BeginPlay() override;

		/** Setup Binding between Inputs and Drivable */
		virtual void SetupInputComponent() override;


		UFUNCTION(BlueprintCallable, category = "Drivable Controller")
		void takeControlOf(TSubclassOf<class ADrivable> drivable);

	private:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ADrivable> linkedDrivable;

		void takeControlOfLinkedDrivable();

		void MoveForward(float ThrottleInput);
		void TurnRight(float SteeringInput);
		void EngageEBrake();
		void ReleaseEBrake();
		void ShiftUp();
		void ShiftDown();
};