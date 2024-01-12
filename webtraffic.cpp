#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std ;
// Names of cities
vector<string> cities = {"Pune", "Nagpur", "Wardha", "Mumbai", "Nashik"};

// for timeday
vector<string> timeOfDay = {"morning", "noon", "evening", "night"};

// For generating random integer in a range whereever needed 
int getRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Here I used structure to store visit entry
struct VisitEntry {
    int userId;
    string timeOfDay;
    int timeSpentMinutes;
};

// Function to generate web traffic data
vector<VisitEntry> generateWebTrafficData(int numCities, int numEntriesPerCity) {
    vector<VisitEntry> webTrafficData;

    for (int cityIndex = 0; cityIndex < numCities; ++cityIndex) {
        for (int entryIndex = 0; entryIndex < numEntriesPerCity; ++entryIndex) {
            VisitEntry entry;
            entry.userId = getRandomInt(1, 30);
            entry.timeOfDay = timeOfDay[getRandomInt(0, 3)]; // 0 to 3 represents morning to night randomly 
            entry.timeSpentMinutes = getRandomInt(1, 120); // Here I take time spend should between 1 to 120 randomly
            webTrafficData.push_back(entry);
        }
    }

    return webTrafficData;
}

int main() {
    srand(time(0)); // Srand function for random time generation 

    // Generate web traffic data
    int numCities = 5;
    int numEntriesPerCity = 100;
    vector<VisitEntry> webTrafficData = generateWebTrafficData(numCities, numEntriesPerCity);

    // Analyze data
    map<string, int> timeOfDayUsers;
    map<string, map<string, int>> cityTimeOfDayUsers; 

    for (const auto& entry : webTrafficData) {
        // Count unique users for each timeofday
        timeOfDayUsers[entry.timeOfDay]++;

        // Count users for each city at each timeofday
        cityTimeOfDayUsers[entry.timeOfDay][cities[(entry.userId - 1) % numCities]]++;
    }

    // Find timeofday with the most unique users
    string maxTimeOfDay;
    int maxUsers = 0;
    for (const auto& entry : timeOfDayUsers) {
        if (entry.second > maxUsers) {
            maxUsers = entry.second;
            maxTimeOfDay = entry.first;
        }
    }

    // Output is here
    cout << "1. Time of day with the most unique users: " << maxTimeOfDay << " (" << maxUsers << " users)\n";

    cout << "2. City with the most users at each time of day:\n";
    for (const auto& timeOfDayEntry : cityTimeOfDayUsers) {
        string timeOfDay = timeOfDayEntry.first;
        for (const auto& cityEntry : timeOfDayEntry.second) {
            string city = cityEntry.first;
            int users = cityEntry.second;
            cout << city << " " << timeOfDay << " " << users << " users\n";
        }
    }

    return 0;
}



