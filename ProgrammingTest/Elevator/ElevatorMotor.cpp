#include "ElevatorMotor.h"

void ElevatorMotor::Step()
{
    if (Direction == ElevatorDirection::Up && CurrentFloor < 9) {
        CurrentFloor++;
    }
    else if (Direction == ElevatorDirection::Down && CurrentFloor > 0) {
        CurrentFloor--;
    }
    else if (Direction == ElevatorDirection::Idle) {
    }
}
