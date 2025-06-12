#include <iostream>
#include <exception>
#include <algorithm>

#include "../includes/Mission.hpp"
#include "../includes/Utilities.h"

std::string name;

int userPoints;
int goalPoints;
int expReward;

Mission::Mission(std::string Name, int UserPoints, int GoalPoints, int ExpReward) {
	name = Name;
	userPoints = UserPoints;
	goalPoints = GoalPoints;
	expReward = ExpReward;
}
void Mission::DisplayInfo() {
	std::cout << "Name: " << name << '\n';
	std::cout << "Reward: " << expReward << " exp \n";
}
void Mission::DisplayInfoWithStatus() {
	std::cout << "Name: " << name << '\n';
	std::cout << "Status: " << userPoints << '/' << goalPoints << '\n';
	std::cout << "Reward: " << expReward << " exp \n";
}

std::vector<Mission>MissionsManager::AllMissions = {
		{"Kill enemies", 0, 30, 150},
		{"Steal cars", 0, 15, 200},
		{"Take down thieves", 0, 20, 300},
		{"Collect items", 0, 75, 75},
		{"Defeat boss", 0, 100, 500}
};

const int MissionsManager::allMissionsSize = MissionsManager::AllMissions.size();

std::vector<std::optional<Mission>>MissionsManager::AvailableMissions;

std::vector<std::optional<Mission>>MissionsManager::ActiveMissions(allMissionsSize);

std::vector<std::optional<Mission>>MissionsManager::CompletedMissions(allMissionsSize);

// Activates the available mission at MissionIndex
void MissionsManager::AcceptMission(int missionIndex) {
	if (missionIndex >= 0 && missionIndex < allMissionsSize) { // if it's a possibly valid index (in range)
		if (!AvailableMissions[missionIndex].has_value()) { // if it's not available
			if (ActiveMissions[missionIndex].has_value()) { // if it's active
				throw(std::invalid_argument("Error: Mission #" + std::to_string(missionIndex) + " is already active!"));
			}

			throw(std::invalid_argument("Error: Mission #" + std::to_string(missionIndex) + " is completed!")); // else, it's completed
		}

		ActiveMissions[missionIndex] = AvailableMissions[missionIndex];
		AvailableMissions[missionIndex] = std::nullopt;

		return;
	}
	
	throw(std::invalid_argument("Index out of range: invalid mission!"));
}

// Updates the active mission at missionIndex
void MissionsManager::UpdateMission(int missionIndex) {
	++ActiveMissions[missionIndex]->userPoints;
}

// Completes the active mission at missionIndex
void MissionsManager::MarkMissionAsCompleted(int missionIndex) {
	CompletedMissions[missionIndex] = ActiveMissions[missionIndex];
	ActiveMissions[missionIndex] = std::nullopt;
}

// Gives up the active mission at missionIndex
void MissionsManager::FailMission(int missionIndex) {
	if (missionIndex >= 0 && missionIndex < allMissionsSize) { // if it's a possibly valid index (in range)
		if (!ActiveMissions[missionIndex].has_value()) { // if it's not active
			if (AvailableMissions[missionIndex].has_value()) { // if it's available
				throw(std::invalid_argument("Error: Mission #" + std::to_string(missionIndex) + " is not active!"));
			}

			throw(std::invalid_argument("Error: Mission #" + std::to_string(missionIndex) + " is completed!")); // else, it's completed
		}

		ActiveMissions[missionIndex]->userPoints = 0; // reset user points
		AvailableMissions[missionIndex] = ActiveMissions[missionIndex];
		ActiveMissions[missionIndex] = std::nullopt;

		return;
	}

	throw(std::invalid_argument("Index out of range: invalid mission!"));
}

// Prints the available missions
void MissionsManager::DisplayAvailableMissions() {
	bool isAllEmpty = true;

	for (const auto& m : AvailableMissions) {
		if (m.has_value()) {
			isAllEmpty = false;
			break;
		}
	}

	if (isAllEmpty) {
		throw(std::invalid_argument("No more available missions!"));
	}

	std::cout << "Available missions list: \n\n";

	for (int i = 0; i < allMissionsSize; ++i) {
		if (AvailableMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			AvailableMissions[i]->DisplayInfo();
			std::cout << '\n';
		}
	}
}

// Prints the active missions
void MissionsManager::DisplayActiveMissionsStatus() {
	bool isAllEmpty = true;

	for (const auto& m : ActiveMissions) {
		if (m.has_value()) {
			isAllEmpty = false;
			break;
		}
	}

	if (isAllEmpty) {
		throw(std::invalid_argument("No active missions yet!"));
	}

	std::cout << "Active missions list: \n\n";

	for (int i = 0; i < allMissionsSize; ++i) {
		if (ActiveMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			ActiveMissions[i]->DisplayInfoWithStatus();
			std::cout << '\n';
		}
	}
}

// Prints the Completed missions
void MissionsManager::DisplayCompletedMissions() {
	bool isAllEmpty = true;

	for (const auto& m : CompletedMissions) {
		if (m.has_value()) {
			isAllEmpty = false;
			break;
		}
	}

	if (isAllEmpty) {
		throw(std::invalid_argument("No completed missions yet!"));
	}
	
	std::cout << "Completed missions list: \n\n";

	for (int i = 0; i < allMissionsSize; ++i) {
		if (CompletedMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			CompletedMissions[i]->DisplayInfo();
			std::cout << '\n';
		}
	}
}

// Simulates all the active missions' completion
void MissionsManager::SimulateMissionsCompletion() {
	bool isAllEmpty = true;

	for (const auto& m : ActiveMissions) {
		if (m.has_value()) {
			isAllEmpty = false;
			break;
		}
	}

	if (isAllEmpty) {
		throw(std::invalid_argument("No active missions yet!"));
	}

	for (int i = 0; i < allMissionsSize; ++i) {
		if (ActiveMissions[i].has_value()) {
			UpdateMission(i);
		}
	}
}

// Checks if there are completed active missions
void MissionsManager::EvaluateMissions() {
	for (int i = 0; i < allMissionsSize; ++i) {
		if (ActiveMissions[i].has_value()) {
			if (ActiveMissions[i]->userPoints == ActiveMissions[i]->goalPoints) {
				std::cout << "Mission \"" << ActiveMissions[i]->name << "\" completed! \n";
				std::cout << "Reward: +" << ActiveMissions[i]->expReward << " exp \n\n";
				Player::UpdatePlayerExp(i); // update player's exp before deleting the mission (handed by CompleteMission method)
				MarkMissionAsCompleted(i);
			}
		}
	}
}