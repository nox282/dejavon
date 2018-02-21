//MIT License Copyright(c) 2017 Nicolas Hamard
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drivable.generated.h"

UCLASS()
class DEJAVON_API ADrivable : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrivable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void MoveForward(float ThrottleInput);

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void TurnRight(float SteeringInput);

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void EngageEBrake();

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void ReleaseEBrake();

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void ShiftUp();

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	virtual void ShiftDown();

	FORCEINLINE class UStaticMeshComponent* GetDrivableMesh() const { return DrivableMesh; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual class UDrivableBehaviorsComponent* GetBehaviorsComponent() const;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DrivableMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* DrivableSpringArm;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* DrivableCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
	class UDrivableBehaviorsComponent* DrivableBehaviors;

	// Sets engine and transmission specs if there are any
	void HandleDrivableSpecs();

	// Sets the proper body mesh if applicable
	void HandleBodyComponent();

	TArray<FTransform> SteeredWheels;
	TArray<FTransform> DriveWheels;
};
