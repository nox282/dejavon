// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrivableWheelComponent.generated.h"


UCLASS(ClassGroup = (DrivableComponent), Blueprintable)
class DEJAVON_API ADrivableWheelComponent : public AActor
{
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		ADrivableWheelComponent();

		class UDrivableWheelMovementComponent* GetWheelMovementComponent();
		UStaticMeshComponent* GetBodyMesh();
		FName GetSocketName();

		void SetSocketName(FName name);

		void ApplyInput(FVector vector);

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	private:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BodyMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		FName SocketName;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DrivableComponent", Meta = (AllowPrivateAccess = "true"))
		UDrivableWheelMovementComponent* WheelMovementComponent;
};
