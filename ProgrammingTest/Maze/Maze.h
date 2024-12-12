#pragma once
#include <string>
#include <unordered_map>

using namespace std;

enum class Direction {
    North,
    South,
    East,
    West,
    Invalid // To handle invalid input
};

Direction StringToDirection(const string& directionStr);

class Room {
public:
    string Name;
    Room* North;
    Room* South;
    Room* East;
    Room* West;

    Room(const string& name);
};

class Maze {
private:
    unordered_map<string, Room*> Rooms;  // Map of room names to Room pointers
    string MazeRepresentation;     // Visual representation of the maze
	string Status;				  // Status message

public:
    Maze();                             // Constructor
    ~Maze();                            // Destructor
    void AddRoom(const string& RoomName);   // Add a new room
    void ConnectRooms(const string& room1, const string& room2, const string& direction);
    void UpdateMazeRepresentation();    // Update the visual representation
    void PrintMazeRepresentation();     // Print the visual representation

	Room* GetRoomByName(const string& name); // Get a room by name
    bool PathExistsTo(Room* startingRoom, const std::string& endingRoomName); // Check if a path exists
    void SetStatus(const string& newStatus);  // Setter for status
};

// Run interactive Maze Challenge
void RunMazeChallenge();

void PrintMazeChallengeOptions();
void ExitToMainMenu(Maze* MazeToCleanup);
int GetPlayerChoice(Maze* ParentMaze);
void AddRoomSelected(Maze* ParentMaze);
void ConnectRoomsSelected(Maze* ParentMaze);
void CheckPathExistsSelected(Maze* ParentMaze);
void ClearMazeConsole();
