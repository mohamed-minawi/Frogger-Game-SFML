#include "Enemy.h"
#include "SFML\Graphics.hpp"
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;



Enemy::Enemy()
{
	//enemy.setTexture(*texture);
	//enemy.setTextureRect(*intrect);
	//enemy.setPosition(position);
	clock.restart();

	xl = x;
	xr = x;
	xu = x;
	xd = x;
	yl = y;
	yr = y;
	yu = y;
	yd = y;

	srand(std::time(NULL));

	scalefactor = new Vector2f;

	positionofother = new Vector2f;
	position = new Vector2f;
	changeinpos = new Vector2f;
	scalefactor = new Vector2f;

	if (!setinitialscale)
	scalefactor->x = scalefactorx;
	scalefactor->y = scalefactory;

	gamedim = new float*[2];

	for (int i = 0; i < 2; i++)
		gamedim[i]= new float;
}

void Enemy::numofrtsprite(int rt)
{
	r = new IntRect[rt];
	right = rt;
}
void Enemy::numofltsprite(int lt)
{
	l = new IntRect[lt];
	left = lt;
}
void Enemy::numofupsprite(int p)
{
	u = new IntRect[p];
	up = p;
}
void Enemy::numofdownsprite(int dn)
{
	d = new IntRect[dn];
	down = dn;
}
//
//void Enemy::sizeright(float v, float w)
//{
//	xr = v;
//	yr = w;
//}
//void Enemy::sizeleft(float v, float w)
//{
//	xl = v;
//	yl = w;
//}
//void Enemy::sizeup(float v, float w)
//{
//	xu = v;
//	yu = w;
//}
//void Enemy::sizedown(float v, float w)
//{
//	xd = v;
//	yd = w;
//}

void Enemy::setrightrect(int num, IntRect& v)
{
	*(r+num - 1) = v;
	xr = v.width;
	yr = v.height;

}
void Enemy::setleftrect(int num, IntRect& v)
{
	*(l + num - 1) = v;

	xl = v.width;
	yl = v.height;
}
void Enemy::setuprect(int num, IntRect& v)
{
	*(l + num - 1) = v;

	xu = v.width;
	yu = v.height;
}
void Enemy::setdownrect(int num, IntRect& v)
{
	*(d + num - 1) = v;
	xd = v.width;
	yd = v.height;
}

void Enemy::repeated(bool flag)
{
	repeat = flag;
}
void Enemy::gamedimension(float** positionb)
{
	
	gamedim = positionb;

	gamewidth = positionb[0][0];
	gamelength = positionb[1][0];

}
void Enemy::repeattime(float watch)
{
	//time = seconds(watch);
	repeatnum = gamewidth / watch;
	//helper = new Sprite[repeatnum];
	enemyspeed = repeatnum;
	/*for (int i = 0; i < repeatnum; i++)
	{
	//helpers[i] = helper;
	/**(helpers + i).setTexture(texture);
	*(helpers + i).setTextureRect(intrect);
	*(helpers + i).setOrigin(x, y);*/

	//}
}
void Enemy::repeatrandom(bool flag)
{
	random = flag;

	//enemys = new Sprite[repeatnum];
	/*if(random)
	enemyspeed = rand() % 20;
	//for (int i = 0; i < repeatnum; i++)
	//{
	//	enemys[i] = enemy;
	//	/**(enemys + i).setTexture(texture);
	//	*(enemys + i).setTextureRect(intrect);
	//	*(enemys + i).setOrigin(x, y);*/
	//}


}
void Enemy::setrandom()
{
		if (random)
	{
		repeatnum = float(rand() % 20);
		enemyspeed = repeatnum;
	}
}

void Enemy::moveright()
{
		if (right > 0)
	{
		enemy.setTextureRect(*(r + movecount%right));
		movecount++;
	}


	enemy.setOrigin(xr / 2, yr / 2);

	enemy.move(enemyspeed, 0);

	gamedimension(gamedim);

	if (repeat)
	{
		if (enemy.getPosition().x - xr / 2 > gamewidth)
		{
			enemy.setPosition(Vector2f((-xr / 2), enemy.getPosition().y));
		}
	}

	movright = true;
	movleft = false;
	movup = false;
	movdown = false;
}
void Enemy::moveleft()
{
	if (left > 0)
	{
		enemy.setTextureRect(*(l + movecount%left));
		movecount++;
	}

	enemy.setOrigin(xl / 2, yl / 2);
	enemy.move(-enemyspeed, 0);

	gamedimension(gamedim);

	if (repeat)
	{
		if (enemy.getPosition().x + xl / 2 < 0)
		{
			enemy.setPosition(gamewidth + xl / 2, enemy.getPosition().y);
		}
	}

	movright = false;
	movleft = true;
	movup = false;
	movdown = false;
}
void Enemy::moveup()
{
		if (up > 1)
	{
		enemy.setTextureRect(*(u + movecount%up));
		movecount++;
	}


	enemy.setOrigin(xu / 2, yu / 2);

	enemy.move(0, -enemyspeed);

	gamedimension(gamedim);

	if (repeat)
	{
		if (enemy.getPosition().y + yu / 2 < 0)
		{
			enemy.setPosition(enemy.getPosition().x, gamelength + yu / 2);
		}
	}

	movright = false;
	movleft = false;
	movup = true;
	movdown = false;


}
void Enemy::movedown()
{
	if (down > 1)
	{
		enemy.setTextureRect(*(d + movecount%down));
		movecount++;
	}

	enemy.setOrigin(xd / 2, yd / 2);

	enemy.move(0, enemyspeed);

	gamedimension(gamedim);

	if (repeat)
	{
		if (enemy.getPosition().y - yd / 2 >gamelength)
		{
			enemy.setPosition(enemy.getPosition().x, -yd / 2);
		}
	}

	movright = false;
	movleft = false;
	movup = false;
	movdown = true;
}

void Enemy::speed(float f)
{
	enemyspeed = f;

}
void Enemy::settexture(Texture& texturep)
{
	texture = &texturep;
	enemy.setTexture(*texture);
}
void Enemy::setintrect(IntRect& intrectp)
{
	intrect = &intrectp;
	enemy.setTextureRect(*intrect); 
	x = intrectp.width;
	y = intrectp.height;
	xl = x;
	xr = x;
	xu = x;
	xd = x;
	yl = y;
	yr = y;
	yu = y;
	yd = y;
	enemy.setOrigin(x / 2, y / 2);
}
void Enemy::setpos(Vector2f* positionb, Vector2f* difference)
{
	position = positionb;
	changeinpos = difference;

	positionofother->x = positionb->x + difference->x;
	positionofother->y = positionb->y + difference->y;
	
	enemy.setPosition(*positionofother);
}

Vector2f* Enemy::returnpos()
{
 	position->x= enemy.getPosition().x;
	position->y = enemy.getPosition().y;


	return position;
}
void Enemy::rotate(float angle)
{
	enemy.rotate(angle);
}

Vector2f Enemy::returnsize()
{
		if (movright)
	{
		size.x = xr;
		size.y = yr;
	}
	else if (movleft)
	{
		size.x = xl;
		size.y = yl;
	}
	else if (movup)
	{
		size.x = xu;
		size.y = yu;
	}
	else if (movdown)
	{
		size.x = xd;
		size.y = yd;
	}

	else
	{
		size.x = x;
		size.y = y;

	}
	return	size;
}
void Enemy::scale(Vector2f* scalevalue)
{
	scalefactorx *= scalevalue->x;
	scalefactory *= scalevalue->y;

	//player.scale(Vector2f(1/ scalefactorx, 1/ scalefactory));
	enemy.scale(Vector2f(scalefactorx, scalefactory));// (gamedim->y / 20) / y));

	scalefactor->x = scalefactorx;
	scalefactor->y = scalefactory;

	scalefactorx *= scalefactor->x;
	scalefactory *= scalefactor->y;

	x *= scalefactor->x;
	xl *= scalefactor->x;
	xr *= scalefactor->x;
	xu *= scalefactor->x;
	xd *= scalefactor->x;
	yl *= scalefactor->y;
	yr *= scalefactor->y;
	yu *= scalefactor->y;
	yd *= scalefactor->y;
	y *= scalefactor->y;
	//helper.scale(*scalefactor);
	
	setpos(position, changeinpos);
}


void Enemy::render(RenderWindow & window)
{

		window.draw(enemy);
}

Vector2f* Enemy::returnscale()
{
	return scalefactor;
}

