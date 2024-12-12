#include "SortLetters.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

string SortLetters(const string& input, const string& sortOrder)
{
    // Create a map to store the priority of each character in the sortOrder
   unordered_map<char, int> priorityMap;
    for (size_t i = 0; i < sortOrder.size(); ++i) {
        priorityMap[sortOrder[i]] = static_cast<int>(i);
    }

    // Copy input string into a vector for sorting
    vector<char> inputChars(input.begin(), input.end());

    // Sort input characters based on the priority map
    sort(inputChars.begin(), inputChars.end(), [&priorityMap](char a, char b) {
        return priorityMap[a] < priorityMap[b];
        });

    // Return the sorted string
    return string(inputChars.begin(), inputChars.end());
}

void RunSortLetters()
{
    cout << "\n=== Sort Letters ===\n";
    cout << "Enter a string to sort: ";
    string inputStr;
    cin.ignore(); // Ignore leftover newline character
    getline(std::cin, inputStr);

    cout << "Enter the sort order string: ";
    string sortOrder;
    getline(std::cin, sortOrder);

    string sortedStr = SortLetters(inputStr, sortOrder);
    cout << "Sorted string: " << sortedStr << "\n\n";
}
