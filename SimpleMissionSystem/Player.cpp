#include "../includes/Player.h"
#include "../includes/Mission.h"

int Player::expPoints = 0;

void Player::UpdatePlayerExp(int MissionIndex) {
	expPoints += MissionsManager::ActiveMissions[MissionIndex]->expReward;
}