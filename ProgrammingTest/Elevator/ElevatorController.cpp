#include "ElevatorController.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Atomic variables for timer control
std::atomic<bool> IsRunning(true);

void TimerThread(ElevatorController* EController) {
    while (IsRunning) {
        this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second
        EController->StepSimulation(); // Call the StepSimulation function
    }
}

void RunElevatorChallenge()
{
    // Initialize Elevator Motor and Controller
    ElevatorMotor* Motor = new ElevatorMotor();
    ElevatorController* EController = new ElevatorController();
    EController->SetControlledMotor(Motor);

    // Start the timer thread
    thread Timer(TimerThread, EController);

    while (true) {
        // Refresh the screen only when ShouldRefreshScreen is true
        EController->PrintElevatorChallangeScreen();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 0:
            IsRunning = false; // Stop the timer thread
            Timer.join();      // Wait for the thread to finish
            CleanupElevatorSimulator(Motor, EController);
            cout << "Exiting Elevator Controller...\n";
            return; // Exit to main menu
        case 1: {
			EController->bWaitingForInput = true; // Set refresh flag before input
            int floor;
            cout << "Enter floor to summon: ";
            cin >> floor;
            EController->SummonElevator(floor); // Handle summon request
            EController->bWaitingForInput = false; 
            break;
        }
        case 2: {
            EController->bWaitingForInput = true;
            int floor;
            cout << "Enter destination floor: ";
            cin >> floor;
            EController->SelectDestination(floor); // Handle destination request
            EController->bWaitingForInput = false; // Set refresh flag after input
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
            EController->SetShouldRefresh(true); // Set refresh flag for invalid input
        }
    }
}

void ElevatorController::SummonElevator(int floor)
{
    if (floor < 0 || floor > 9) {
        SetStatusMessage("Invalid floor. Please select a floor between 0 and 9.");
        return;
    }

    // Check if a request already exists for this floor
    for (const pair<const int, ElevatorRequest>& Request : RequestQueue) {
        if (Request.second.SummonFloor == floor && !Request.second.HasDestination) {
            SetStatusMessage("Floor " + to_string(floor) + " is already queued.");
            return;
        }
    }

    // Add the request to the queue with a unique ID
    RequestQueue[NextRequestId++] = ElevatorRequest(floor);
    SetStatusMessage("Summon request received for floor " + to_string(floor) + ".");
}

void ElevatorController::SelectDestination(int floor)
{
    if (floor < 0 || floor > 9) {
        SetStatusMessage("Invalid floor. Please select a floor between 0 and 9.");
        return;
    }

    // Assign the destination to the most recent request without a destination
    for (pair<const int, ElevatorRequest>& Request : RequestQueue) {
        if (!Request.second.HasDestination && ControlledMotor->GetCurrentFloor() == Request.second.SummonFloor) {
            Request.second.DestinationFloor = floor;
            Request.second.HasDestination = true;
            SetStatusMessage("Destination set to floor " + to_string(floor) + ".");
            return;
        }
    }

    SetStatusMessage("No active request to set a destination for.");
}

void ElevatorController::StepSimulation()
{
    if (!ControlledMotor) return;

    // Increment the elapsed time
    CurrentElapsedTime++;

    // Check if the elevator is waiting
    if (IsWaiting) {
        CurrentWaitTime++;
        if (CurrentWaitTime >= StayAtFloorTime) {
            // Stop waiting and reset the timer
            IsWaiting = false;
            CurrentWaitTime = 0;
            SetStatusMessage("Leaving floor " + to_string(ControlledMotor->GetCurrentFloor()));
        }
        else {
            SetStatusMessage("Waiting at floor " + to_string(ControlledMotor->GetCurrentFloor()) + "...");
        }
        SetShouldRefresh(true);
        return;
    }

    // Process summon requests
    if (!RequestQueue.empty()) {
        pair<const int, ElevatorRequest>& NextRequest = *RequestQueue.begin(); // Get the first request
        int targetFloor = NextRequest.second.HasDestination
            ? NextRequest.second.DestinationFloor
            : NextRequest.second.SummonFloor;

        int currentFloor = ControlledMotor->GetCurrentFloor();

        if (currentFloor < targetFloor) {
            ControlledMotor->SetDirection(ElevatorDirection::Up);
            ControlledMotor->Step();
            SetStatusMessage("Moving up to floor " + to_string(targetFloor));
        }
        else if (currentFloor > targetFloor) {
            ControlledMotor->SetDirection(ElevatorDirection::Down);
            ControlledMotor->Step();
            SetStatusMessage("Moving down to floor " + to_string(targetFloor));
        }
        else {
            // Arrived at the target floor
            ControlledMotor->SetDirection(ElevatorDirection::Idle);
            IsWaiting = true; // Start waiting
            RequestQueue.erase(NextRequest.first); // Remove the processed request
            SetStatusMessage("Arrived at floor " + to_string(currentFloor));
        }

        SetShouldRefresh(true); // Trigger screen refresh
        return;
    }

    // No requests in the queue; elevator is idle
    ControlledMotor->SetDirection(ElevatorDirection::Idle);
    SetStatusMessage("Idle at floor " + to_string(ControlledMotor->GetCurrentFloor()));
    SetShouldRefresh(true);
}

void ElevatorController::PrintElevatorChallangeScreen()
{
    if (bWaitingForInput)  return;
    if (!ShouldRefreshScreen) return;

    ClearElevatorConsole();
	PrintBuldingWithElevator(ControlledMotor->GetCurrentFloor());
    cout << "Elapsed Time: " << CurrentElapsedTime << " seconds\n";
	cout << "Status: " << GetStatusMessage() << "\n";
    PrintElevatorOptions();
    ShouldRefreshScreen = false;
}

void ElevatorController::SetShouldRefresh(bool Refresh)
{
	ShouldRefreshScreen = Refresh;
    PrintElevatorChallangeScreen();
}


void PrintBuldingWithElevator(const int CurrentElevatorFloor)
{
    // Print the building with elevator position
    cout << "=== Elevator Controller ===\n";
    cout << "=== Building ===\n";
    for (int floor = 9; floor >= 0; --floor) {
        cout << "Floor " << floor << ": ";
        if (floor == CurrentElevatorFloor) {
            cout << "|[E]|";  // Elevator is here
        }
        else {
            cout << "|   |";  // Empty floor
        }
        cout << "\n";
    }
    cout << "===============\n";
}

void CleanupElevatorSimulator(ElevatorMotor* Motor, ElevatorController* EController)
{
    delete Motor;
    delete EController;
}

void PrintElevatorOptions()
{
    cout << "Options:\n";
    cout << "1: Summon Elevator\n";
    cout << "2: Select Destination\n";
    cout << "0: Exit to Main Menu\n";
}

void ClearElevatorConsole()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Unix-based systems
#endif
}
