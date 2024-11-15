#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Define the Log class representing a piece of wood
class Log {
public:
    string species;
    double length;
    int years;

    Log(string sp, double len, int yr) : species(sp), length(len), years(yr) {}
};

// Function to count the number of logs with the same species and age in the stack
int countLogsBySpeciesAndYears(stack<Log>& logStack, const string& targetSpecies, int targetYears) {
    stack<Log> tempStack;  // Temporary stack to hold logs
    int matchingCount = 0;

    // Check each log in the stack
    while (!logStack.empty()) {
        Log currentLog = logStack.top();
        logStack.pop();

        // If the log has the same species and age
        if (currentLog.species == targetSpecies && currentLog.years == targetYears) {
            matchingCount++;
        }

        // Push the log into the temporary stack to preserve original data
        tempStack.push(currentLog);
    }

    // Move the logs back from the temporary stack to the main stack
    while (!tempStack.empty()) {
        logStack.push(tempStack.top());
        tempStack.pop();
    }

    return matchingCount;
}

int main() {
    // Create a stack and add logs to it
    stack<Log> logStack;
    logStack.push(Log("Maple", 3.0, 8));
    logStack.push(Log("Birch", 2.5, 12));
    logStack.push(Log("Maple", 3.2, 8));
    logStack.push(Log("Pine", 4.1, 15));
    logStack.push(Log("Maple", 2.9, 8));

    // Count the number of logs of species "Maple" with age 8
    int result = countLogsBySpeciesAndYears(logStack, "Maple", 8);
    cout << "Number of 'Maple' logs with age 8: " << result << endl;

    return 0;
}


