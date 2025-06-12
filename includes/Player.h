#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct Player {
public:
	static int expPoints;

	// Adds the experience reward from the active mission at MissionIndex to player's exp.
	static void UpdatePlayerExp(int MissionIndex);
};

#endif // PLAYER_H