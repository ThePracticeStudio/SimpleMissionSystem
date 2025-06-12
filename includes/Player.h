#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct Player {
public:
	static int expPoints;

	static void UpdatePlayerExp(int MissionIndex);
};

#endif // PLAYER_H