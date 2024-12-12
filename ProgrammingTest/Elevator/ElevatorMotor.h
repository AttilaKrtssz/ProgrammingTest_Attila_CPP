#pragma once

enum class ElevatorDirection {
    Idle,
    Up,
    Down
};

class ElevatorMotor {

public:
    ElevatorMotor() {};               // Constructor

    // Getters
    int GetCurrentFloor() const { return CurrentFloor; }          // Returns the current floor
    ElevatorDirection GetCurrentDirection() const { return Direction; }  // Returns the current direction

    void SetDirection(ElevatorDirection NewDirection) { Direction = NewDirection;}
    // Movement
    void Step();                   // Moves the elevator one step (to-do)

private:
    int CurrentFloor = 0;              // The current floor of the elevator
    ElevatorDirection Direction = ElevatorDirection::Idle;   // The current direction of the elevator

};