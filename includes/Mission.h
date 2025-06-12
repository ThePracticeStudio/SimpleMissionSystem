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
	static std::vector<std::optional<Mission>>AvailableMissions;
	static std::vector<std::optional<Mission>>ActiveMissions;
	static std::vector<std::optional<Mission>>CompletedMissions;
	static std::vector<Mission>AllMissions;

	static void AcceptMission(int MissionIndex);
	static void UpdateMission(int MissionIndex);
	static void CompleteMission(int MissionIndex);
	static void FailMission(int MissionIndex);

	static void DisplayAvailableMissions();
	static void DisplayActiveMissionsStatus();
	static void DisplayCompletedMissions();
	static void SimulateMissionsCompletion();
	static void CheckForCompletedMissions();
};

#endif // MISSION_H