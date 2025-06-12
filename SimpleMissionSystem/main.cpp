#include <iostream>
#include <limits>

#include "../includes/Mission.h"
#include "../includes/Player.h"
#include "../includes/utilities.h"

int main() {
	for (const auto& m : MissionsManager::AllMissions) {
		MissionsManager::AvailableMissions.push_back(m); // Mission verrà convertito in std::optional<Mission>
	}

	int option;

	bool UserWantsToExit;
	int missionIndex{};

	do {
		UserWantsToExit = false;

		std::cout << "--- Missions Menu --- \n";
		std::cout << "1. Start a mission; \n";
		std::cout << "2. Show active missions' status; \n";
		std::cout << "3. Give up a mission; \n";
		std::cout << "4. Simulate missions completion; \n";
		std::cout << "5. Show completed missions; \n";
		std::cout << "6. Show current exp; \n";
		std::cout << "7. Quit \n";
		std::cout << '\n';

		if (!getValidInput("> ", option)) {
			std::cerr << "Invalid input format! \n\n";
			ClearAndIgnore();
			continue;
		}

		switch (option) {
			case 1:
			{
				try {
					MissionsManager::DisplayAvailableMissions();
				}
				catch (const std::invalid_argument& e) {
					std::cout << e.what();
					std::cout << "\n\n";
					continue;
				}

				if (!getValidInput("Which mission do you wish to accept? \n", missionIndex)) {
					std::cerr << "Invalid input: please enter a number. \n\n";
					ClearAndIgnore();
					continue;
				}

				try {
					MissionsManager::AcceptMission(missionIndex);
				}
				catch (const std::invalid_argument& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
					continue;
				}

				std::cout << "New mission activated! \n\n";

				break;
			}
			case 2:
			{
				try {
					MissionsManager::DisplayActiveMissionsStatus();
				}
				catch (const std::invalid_argument& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
					continue;
				}

				break;
			}
			case 3:
			{
				try {
					MissionsManager::DisplayActiveMissionsStatus();
				}
				catch (const std::invalid_argument& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
					continue;
				}

				if (!getValidInput("Which missions do you wish to give up? \n", missionIndex)) {
					std::cerr << "Invalid input format! \n\n";
					ClearAndIgnore();
					continue;
				}
				
				try {
					MissionsManager::FailMission(missionIndex);
				}
				catch (const std::exception& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
					continue;
				}

				std::cout << "Mission given up. You can still carry it out again. \n\n";

				break;
			}
			case 4:
			{
				try {
					MissionsManager::SimulateMissionsCompletion();
				}
				catch (const std::invalid_argument& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
					continue;
				}

				std::cout << "Missions updated! \n\n";

				MissionsManager::CheckForCompletedMissions();

				break;
			}
			case 5:
			{
				try {
					MissionsManager::DisplayCompletedMissions();
				}
				catch (const std::invalid_argument& e) {
					printErrorMessage(e);
					std::cout << "\n\n";
				}

				break;
			}
			case 6:
			{
				std::cout << "Current player's exp: " << Player::expPoints << "\n\n";
				break;
			}
			case 7:
			{
				UserWantsToExit = true;
				break;
			}
			default:
			{
				std::cerr << "Invalid option! \n\n";
				break;
			}
		}

		ClearAndIgnore();

	} while (!UserWantsToExit);

	std::cout << "Goodbye! \n";
	std::cout << "Exiting... \n";

	return 0;
}