#include <iostream>
#include <exception>
#include <algorithm>

#include "../includes/Mission.h"
#include "../includes/utilities.h"

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

std::vector<std::optional<Mission>>MissionsManager::AvailableMissions;

std::vector<std::optional<Mission>>MissionsManager::ActiveMissions(AllMissions.size());

std::vector<std::optional<Mission>>MissionsManager::CompletedMissions(AllMissions.size());

void MissionsManager::AcceptMission(int MissionIndex) {
	if (MissionIndex >= 0 && MissionIndex < AllMissions.size()) { // if it's a possibly valid index (in range)
		if (!AvailableMissions[MissionIndex].has_value()) { // if it's not available
			if (ActiveMissions[MissionIndex].has_value()) { // if it's active
				throw(std::invalid_argument("Error: Mission #" + std::to_string(MissionIndex) + " is already active!"));
			}

			throw(std::invalid_argument("Error: Mission #" + std::to_string(MissionIndex) + " is completed!")); // else, it's completed
		}

		ActiveMissions[MissionIndex] = AvailableMissions[MissionIndex];
		AvailableMissions[MissionIndex] = std::nullopt;

		return;
	}
	
	throw(std::invalid_argument("Index out of range: invalid mission!"));
}
void MissionsManager::UpdateMission(int MissionIndex) {
	++ActiveMissions[MissionIndex]->userPoints;
}
void MissionsManager::CompleteMission(int MissionIndex) {
	CompletedMissions[MissionIndex] = ActiveMissions[MissionIndex];
	ActiveMissions[MissionIndex] = std::nullopt;
}

void MissionsManager::FailMission(int MissionIndex) {
	if (MissionIndex >= 0 && MissionIndex < AllMissions.size()) { // if it's a possibly valid index (in range)
		if (!ActiveMissions[MissionIndex].has_value()) { // if it's not active
			if (AvailableMissions[MissionIndex].has_value()) { // if it's available
				throw(std::invalid_argument("Error: Mission #" + std::to_string(MissionIndex) + " is not active!"));
			}

			throw(std::invalid_argument("Error: Mission #" + std::to_string(MissionIndex) + " is completed!")); // else, it's completed
		}

		ActiveMissions[MissionIndex]->userPoints = 0; // reset user points
		AvailableMissions[MissionIndex] = ActiveMissions[MissionIndex];
		ActiveMissions[MissionIndex] = std::nullopt;

		return;
	}

	throw(std::invalid_argument("Index out of range: invalid mission!"));
}

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

	for (int i = 0; i < AllMissions.size(); ++i) {
		if (AvailableMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			AvailableMissions[i]->DisplayInfo();
			std::cout << '\n';
		}
	}
}

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

	for (int i = 0; i < AllMissions.size(); ++i) {
		if (ActiveMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			ActiveMissions[i]->DisplayInfoWithStatus();
			std::cout << '\n';
		}
	}
}

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

	for (int i = 0; i < CompletedMissions.size(); ++i) {
		if (CompletedMissions[i].has_value()) {
			std::cout << "Mission #" << i << '\n';
			CompletedMissions[i]->DisplayInfo();
			std::cout << '\n';
		}
	}
}
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

	for (int i = 0; i < ActiveMissions.size(); ++i) {
		if (ActiveMissions[i].has_value()) {
			UpdateMission(i);
		}
	}
}

void MissionsManager::CheckForCompletedMissions() {
	for (int i = 0; i < ActiveMissions.size(); ++i) {
		if (ActiveMissions[i].has_value()) {
			if (ActiveMissions[i]->userPoints == ActiveMissions[i]->goalPoints) {
				std::cout << "Mission \"" << ActiveMissions[i]->name << "\" completed! \n";
				std::cout << "Reward: " << ActiveMissions[i]->expReward << " exp \n\n";
				Player::UpdatePlayerExp(i); // update player's exp before deleting the mission (handed by CompleteMission method)
				CompleteMission(i);
			}
		}
	}
}