// ProgrammingTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AllDigitsUnique/AllDigitsUnique.h"
#include "SortLetters.h"
#include "Maze/Maze.h"
#include "Elevator/ElevatorController.h"

using namespace std;


void ClearMainConsole()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Unix-based systems
#endif
}

void PrintMenu()
{
    ClearMainConsole();
    cout << "========== Programming Test Menu ==========\n";
    cout << "1. All Digits Unique\n";
    cout << "2. Sort Letters \n";
    cout << "3. Maze of Interconnected Rooms \n";
    cout << "4. Elevator Controller \n";
    cout << "Enter the number of the challenge you want to run (or 0 to exit): ";
}



int main()
{
    while (true) {
        PrintMenu();

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1:
            RunAllDigitsUnique();
            break;
        case 2:
            RunSortLetters();
            break;
        case 3:
            RunMazeChallenge();
        case 4:
            RunElevatorChallenge();
            break;
        default:
            cout << "Invalid choice. Please try again.\n\n";
            break;
        }
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
