#pragma once
#include "ElevatorControllerBase.h"
#include "ElevatorMotor.h"
#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

struct ElevatorRequest {
	int SummonFloor;       // The floor where the elevator is summoned
	int DestinationFloor;  // The destination floor (set when the user selects it)
	bool HasDestination;   // Flag to determine if a destination has been set

	// Default constructor
	ElevatorRequest()
		: SummonFloor(-1), DestinationFloor(-1), HasDestination(false) {}

	// Parameterized constructor
	ElevatorRequest(int summonFloor)
		: SummonFloor(summonFloor), DestinationFloor(-1), HasDestination(false) {}
};

class ElevatorController : public ElevatorControllerBase
{
public:
	/* Start of ElevatorController Base overrides*/
	void SummonElevator(int floor) override;
	void SelectDestination(int floor) override;
	void StepSimulation() override;
	/* End of ElevatorController Base overrides*/

	void SetControlledMotor(ElevatorMotor* InMotor) { ControlledMotor = InMotor;}

	void PrintElevatorChallangeScreen();
	bool GetShouldRefreshScreen() const { return ShouldRefreshScreen; }
	void SetShouldRefresh(bool Refresh);
	void UpdateElapsedTime(int ElapsedSeconds) { CurrentElapsedTime = ElapsedSeconds; }

	bool bWaitingForInput = false;

	const string& GetStatusMessage() const { return StatusMessage;}
	void SetStatusMessage(const string& NewStatus) { StatusMessage = NewStatus; }
private:
	ElevatorMotor* ControlledMotor = nullptr;
	int CurrentChoice = -1;

	bool ShouldRefreshScreen = true;
	int CurrentElapsedTime = 0;

	map<int, ElevatorRequest> RequestQueue;
	int NextRequestId = 0;

	int StayAtFloorTime = 5;
	int CurrentWaitTime = 0;
	bool IsWaiting = false;

	string StatusMessage = "";
};

void RunElevatorChallenge();
void PrintElevatorOptions();
void ClearElevatorConsole();
void PrintBuldingWithElevator(const int CurrentElevatorFloor);
void CleanupElevatorSimulator(ElevatorMotor* Motor, ElevatorController* EController);