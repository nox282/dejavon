// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DrivableWheelMovementComponent.generated.h"


UCLASS()
class DEJAVON_API UDrivableWheelMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	public:
		UDrivableWheelMovementComponent();

		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
