#pragma once
#include <iostream>

void ClearConsole()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Unix-based systems
#endif
}