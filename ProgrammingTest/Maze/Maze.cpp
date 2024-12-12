#include "Maze.h"
#include <iostream>
#include <sstream>
#include "stack"
#include "unordered_set"


// Constructor for Room
Room::Room(const string& name)
    : Name(name), North(nullptr), South(nullptr), East(nullptr), West(nullptr) {}

// Constructor for Maze
Maze::Maze() : MazeRepresentation(""), Status("") {
    cout << "Maze created.\n";
}

// Destructor for Maze
Maze::~Maze() {
    for (pair<const string, Room*>& RoomNamePointerPair : Rooms)
    {
        delete RoomNamePointerPair.second;
    }
    Rooms.clear();
    cout << "Maze destroyed.\n";
}

// Add a room to the maze
void Maze::AddRoom(const string& RoomName) {
    // Check if the room already exists
    if (Rooms.find(RoomName) != Rooms.end()) {
        SetStatus("Room \"" + RoomName + "\" already exists.");
        return;
    }

    // Create a new room and add it to the map
    Room* newRoom = new Room(RoomName);
    Rooms[RoomName] = newRoom;

    SetStatus("Room \"" + RoomName + "\" added successfully.");

    // Update the visual representation of the maze
    UpdateMazeRepresentation();
}

void Maze::ConnectRooms(const string& room1, const string& room2, const string& direction)
{
    // Find the rooms
    Room* r1 = GetRoomByName(room1);
    Room* r2 = GetRoomByName(room2);

    if (!r1 || !r2) {
        SetStatus("One or both rooms do not exist.");
        return;
    }

    // Convert direction string to Direction enum
    Direction Localdir = StringToDirection(direction);

    if (Localdir == Direction::Invalid) {
        SetStatus("Invalid direction. Use north, south, east, or west.");
        return;
    }

    // Connect rooms based on the direction
    switch (Localdir) {
    case Direction::North:
        r1->North = r2;
        break;
    case Direction::South:
        r1->South = r2;
        break;
    case Direction::East:
        r1->East = r2;
        break;
    case Direction::West:
        r1->West = r2;
        break;
    default:
        // This case should never happen due to the enum validation above
        break;
    }

    SetStatus("Connected \"" + room1 + "\" to \"" + room2 + "\" via \"" + direction + "\".");

    // Update the maze representation
    UpdateMazeRepresentation();

}

// Update the maze's visual representation
void Maze::UpdateMazeRepresentation() {
    stringstream ss;

    ss << "Current Maze:\n";
    for (const auto& pair : Rooms) {
        Room* room = pair.second;
        ss << room->Name << ": ";
        if (room->North) ss << "North -> " << room->North->Name << ", ";
        if (room->South) ss << "South -> " << room->South->Name << ", ";
        if (room->East) ss << "East -> " << room->East->Name << ", ";
        if (room->West) ss << "West -> " << room->West->Name << ", ";
        ss << "\n";
    }

    MazeRepresentation = ss.str();
}

// Print the maze's visual representation
void Maze::PrintMazeRepresentation() {
    cout << MazeRepresentation << "\n";
	cout << "Status: " << Status << "\n";
}

Room* Maze::GetRoomByName(const string& name)
{
	if (Rooms.find(name) != Rooms.end()) {
		return Rooms[name];
	}
    return nullptr;
}
Direction StringToDirection(const string& directionStr)
{
    if (directionStr == "north") return Direction::North;
    if (directionStr == "south") return Direction::South;
    if (directionStr == "east") return Direction::East;
    if (directionStr == "west") return Direction::West;
    return Direction::Invalid;
}


bool Maze::PathExistsTo(Room* startingRoom, const std::string& endingRoomName)
{
    if (startingRoom == nullptr)
    {
		SetStatus("Starting room does not exist.");
		return false;
    }
    if (endingRoomName.empty())
    {
		SetStatus("Ending room name is empty.");
		return false;
    }
    // If the starting room is the target room
    if (startingRoom->Name == endingRoomName)
    {
		SetStatus("Starting room is the target room.");
		return true;
    }

    // Set to track visited rooms
    unordered_set<Room*> visited;

    // Stack for DFS
    stack<Room*> toVisit;

    toVisit.push(startingRoom);

    while (!toVisit.empty()) {
        Room* currentRoom = toVisit.top();
        toVisit.pop();

        if (visited.find(currentRoom) != visited.end()) continue;
        visited.insert(currentRoom);

        if (currentRoom->North && currentRoom->North->Name == endingRoomName) {
            SetStatus("Path exists from \"" + startingRoom->Name + "\" to \"" + endingRoomName + "\".");
            return true;
        }
        if (currentRoom->South && currentRoom->South->Name == endingRoomName) {
            SetStatus("Path exists from \"" + startingRoom->Name + "\" to \"" + endingRoomName + "\".");
            return true;
        }
        if (currentRoom->East && currentRoom->East->Name == endingRoomName) {
            SetStatus("Path exists from \"" + startingRoom->Name + "\" to \"" + endingRoomName + "\".");
            return true;
        }
        if (currentRoom->West && currentRoom->West->Name == endingRoomName) {
            SetStatus("Path exists from \"" + startingRoom->Name + "\" to \"" + endingRoomName + "\".");
            return true;
        }

        if (currentRoom->North) toVisit.push(currentRoom->North);
        if (currentRoom->South) toVisit.push(currentRoom->South);
        if (currentRoom->East) toVisit.push(currentRoom->East);
        if (currentRoom->West) toVisit.push(currentRoom->West);
    }

    SetStatus("No path exists from \"" + startingRoom->Name + "\" to \"" + endingRoomName + "\".");
    return false;
}

void Maze::SetStatus(const string& newStatus)
{
	Status = newStatus;
}

void RunMazeChallenge() {
    Maze* MazeInstance = new Maze();

    while (true) {
        PrintMazeChallengeOptions();
        if (MazeInstance) MazeInstance->PrintMazeRepresentation();
		int Selection = GetPlayerChoice(MazeInstance);
        switch (Selection) {
        case 0:
            ExitToMainMenu(MazeInstance);
            return;
        case 1:
            AddRoomSelected(MazeInstance);
            break;
        case 2:
            ConnectRoomsSelected(MazeInstance);
            break;
        case 3:
            CheckPathExistsSelected(MazeInstance);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        MazeInstance->PrintMazeRepresentation();
    }
}

void PrintMazeChallengeOptions()
{
    ClearMazeConsole();

    cout << "\n=== Maze Challenge ===\n";
    cout << "Options:\n";
    cout << "1: Add a room\n";
    cout << "2: Connect rooms\n";
    cout << "3: Check if a path exists\n";
    cout << "0: Exit to main menu\n";
}

void ExitToMainMenu(Maze* MazeToCleanup)
{
    delete MazeToCleanup;  // Clean up allocated memory
    cout << "Exiting Maze Challenge and returning to the main menu...\n";
}

int GetPlayerChoice(Maze* ParentMaze)
{
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    // Validate input
    if (cin.fail()) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        ParentMaze->SetStatus("Invalid input! Please enter a number.");
        return -1; // Return an invalid choice
    }

    return choice;
}

void AddRoomSelected(Maze* ParentMaze)
{
    cout << "Enter room name: ";
    string roomName;
    cin >> roomName;

    ParentMaze->AddRoom(roomName);
}

void ConnectRoomsSelected(Maze* ParentMaze)
{
    cout << "Enter first room name: ";
    string room1;
    cin >> room1;
    cout << "Enter second room name: ";
    string room2;
    cin >> room2;
    cout << "Enter direction (north, south, east, west): ";
    string direction;
    cin >> direction;

    ParentMaze->ConnectRooms(room1, room2, direction);
}

void CheckPathExistsSelected(Maze* ParentMaze)
{
    cout << "Enter starting room name: ";
    string startRoom;
    cin >> startRoom;
    cout << "Enter target room name: ";
    string targetRoom;
    cin >> targetRoom;

    Room* startingRoom = ParentMaze->GetRoomByName(startRoom);
    if (!startingRoom) {
        cout << "Starting room does not exist.\n";
        return;
    }
    bool pathExists = ParentMaze->PathExistsTo(startingRoom, targetRoom);
    if (pathExists) {
        cout << "Path exists from \"" << startRoom << "\" to \"" << targetRoom << "\".\n";
    }
    else {
        cout << "No path exists from \"" << startRoom << "\" to \"" << targetRoom << "\".\n";
    }
}

void ClearMazeConsole()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Unix-based systems
#endif
}
