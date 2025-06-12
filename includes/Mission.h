#ifndef MISSION_H
#define MISSION_H

#include <string>
#include <vector>
#include <optional>

#include "../includes/Player.h"

class Mission {
public:
	std::string name;

	int userPoints;
	int goalPoints;
	int expReward;

	Mission(std::string Name, int UserPoints, int GoalPoints, int ExpReward);

	void DisplayInfo();
	void DisplayInfoWithStatus();
};

class MissionsManager {
public:
	static std::vector<Mission>AllMissions;
	static std::vector<std::optional<Mission>>AvailableMissions;
	static std::vector<std::optional<Mission>>ActiveMissions;
	static std::vector<std::optional<Mission>>CompletedMissions;
	
	static const int allMissionsSize;

	// Activates the available mission at missionIndex
	static void AcceptMission(int missionIndex);

	// Updates the active mission at missionIndex
	static void UpdateMission(int missionIndex);

	// Completes the active mission at missionIndex
	static void MarkMissionAsCompleted(int missionIndex);

	// Gives up the active mission at missionIndex
	static void FailMission(int missionIndex);

	// Prints the available missions
	static void DisplayAvailableMissions();

	// Prints the active missions
	static void DisplayActiveMissionsStatus();

	// Prints the Completed missions
	static void DisplayCompletedMissions();

	// Simulates all the active missions' completion
	static void SimulateMissionsCompletion();

	// Checks if there are completed active missions
	static void EvaluateMissions();
};

#endif // MISSION_H