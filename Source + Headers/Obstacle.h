#ifndef Obstacle_h
#define Obstacle_h
#include "SFML\Graphics.hpp"
#include "Enemy.h"
#include "player.h"
#include "Helper.h"
using namespace sf;
using namespace std;

class Obstacle
{
public:
	Obstacle();
	bool ifmet(Player&, Enemy& );
	bool ifmet(Player&, Helper&);
	void playermovewithhelper(Player&, Helper&);
	bool timeup(Clock&, float);
	bool boundary(Player&, int, int, int, int);

};

#endif

//include "Obstacle.cpp"
