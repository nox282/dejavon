//MIT License Copyright(c) 2017 Nicolas Hamard
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drivable.generated.h"

UCLASS()
class DEJAVON_API ADrivable : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrivable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	void MoveForward(float ThrottleInput);

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	void TurnRight(float SteeringInput);

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	void EngageEBrake();

	UFUNCTION(BlueprintCallable, category = "Drivable Controls")
	void ReleaseEBrake();

	FORCEINLINE class UStaticMeshComponent* GetDrivableMesh() const { return DrivableMesh; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drivable", Meta = (BlueprintProtected = "true"))
	float Horsepower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drivable", Meta = (BlueprintProtected = "true"))
	float Brakepower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drivable", Meta = (BlueprintProtected = "true"))
	float MaximumTurnRate;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drivable", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DrivableMesh;

	
};
