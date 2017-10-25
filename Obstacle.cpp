#include "SFML\Graphics.hpp"
#include "Enemy.h"
#include "Helper.h"
#include "player.h"

#include "Obstacle.h"

Obstacle::Obstacle()
{}

bool Obstacle::ifmet(Player& p, Enemy& e)
{
	bool flag = false;
	

	if (((p.returnpos()->x - p.returnsize().width / 2 < e.returnpos()->x + e.returnsize().x/2 ) && (p.returnpos()->x + p.returnsize().width / 2>e.returnpos()->x -e.returnsize().x/2))
		&& ((p.returnpos()->y + p.returnsize().height / 2> e.returnpos()->y - e.returnsize().y / 2) && (p.returnpos()->y - p.returnsize().height / 2 < e.returnpos()->y + e.returnsize().y / 2)))
	{
		flag = true;
	}


	/*if (((p.returnpos()->x-xp/2 < e.returnpos()->x + xe/2) && (p.returnpos()->x+xp/2 >e.returnpos()->x - xe/2))
		&& ((p.returnpos()->y +yp/2> e.returnpos()->y - ye / 2 )&& (p.returnpos()->y-yp/2 < e.returnpos()->y + ye / 2)))
	{
		 flag = true;
	}*/

	return flag;
}
bool Obstacle::ifmet(Player& p, Helper& h)
{
	bool flag = false;

	if(((p.returnpos()->x /*- p.returnsize().width / 2*/ < (h.returnpos()->x + h.returnsize().x /2)) && (p.returnpos()->x /*+ p.returnsize().width / 2*/>h.returnpos()->x - h.returnsize().x/2))
		&& ((p.returnpos()->y /*+ p.returnsize().height / 2*/> h.returnpos()->y - h.returnsize().y / 2) && (p.returnpos()->y /*- p.returnsize().height / 2 */< h.returnpos()->y + h.returnsize().y / 2)))
	{
		flag = true;
	}

	
	/*if (((p.returnpos()->x - xp / 2 < h.returnpos()->x + xh / 2) && (p.returnpos()->x + xp / 2 >h.returnpos()->x - xh / 2))
		&& ((p.returnpos()->y + yp / 2> h.returnpos()->y - yh / 2) && (p.returnpos()->y - yp / 2 < h.returnpos()->y + yh / 2)))
	{
		flag = true;
	}*/

	return flag;
}
void Obstacle::playermovewithhelper(Player& p, Helper& h)
{
	if (h.ifmove())
	{
		p.move(h.playermove());
	}

}
bool Obstacle::timeup(Clock& clock, float time)
{
	bool flag = false;
	if (clock.getElapsedTime() > seconds(time))
		flag = true;
	return flag;
}
bool Obstacle::boundary(Player& p, int x, int y, int gamewidth, int gamelength)
{
	bool flag = false;

	if (((p.returnpos()->x > x) && (p.returnpos()->x < gamewidth))
		&& ((p.returnpos()->y < gamelength) && (p.returnpos()->y > y)))
	{
		flag = true;
	}

	return flag;
}
