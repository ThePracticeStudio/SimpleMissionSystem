#include "../includes/Player.h"
#include "../includes/Mission.h"

int Player::expPoints = 0; // Initialize player's exp to 0

// Adds the experience reward from the active mission at MissionIndex to player's exp.
void Player::UpdatePlayerExp(int MissionIndex) {
	expPoints += MissionsManager::ActiveMissions[MissionIndex]->expReward;
}