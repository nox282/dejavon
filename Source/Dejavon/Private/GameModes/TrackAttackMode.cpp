// MIT LicenseCopyright (c) 2017 Nicolas Hamard

#include "GameModes/TrackAttackMode.h"
#include "Drivable.h"
#include "DrivablePlayerController.h"

ATrackAttackMode::ATrackAttackMode() {

	//tell your custom game mode to use your custom player controller
	PlayerControllerClass = ADrivablePlayerController::StaticClass();
	DefaultPawnClass = ADrivable::StaticClass();
 }
