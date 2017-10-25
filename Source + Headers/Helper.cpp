#include "Helper.h"
#include "SFML\Graphics.hpp"
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;



Helper::Helper()
{
	/*helper.setTexture(*texture);
	helper.setTextureRect(*intrect);
	helper.setPosition(position);*/
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
		gamedim[i] = new float;
}

void Helper::numofrtsprite(int rt)
{
	r = new IntRect[rt];
	right = rt;
}
void Helper::numofltsprite(int lt)
{
	l = new IntRect[lt];
	left = lt;
}
void Helper::numofupsprite(int p)
{
	u = new IntRect[p];
	up = p;
}
void Helper::numofdownsprite(int dn)
{
	d = new IntRect[dn];
	down = dn;
}

//void Helper::sizeright(float v, float w)
//{
//	xr = v;
//	yr = w;
//}
//void Helper::sizeleft(float v, float w)
//{
//	xl = v;
//	yl = w;
//}
//void Helper::sizeup(float v, float w)
//{
//	xu = v;
//	yu = w;
//}
//void Helper::sizedown(float v, float w)
//{
//	xd = v;
//	yd = w;
//}

void Helper::setrightrect(int num, IntRect& v)
{
	*(r + num - 1) = v;

	xr = v.width;
	yr = v.height;
}
void Helper::setleftrect(int num, IntRect& v)
{
	*(l + num - 1) = v;

	xl = v.width;
	yl = v.height;
}
void Helper::setuprect(int num, IntRect& v)
{
	*(l + num - 1) = v;

	xu = v.width;
	yu = v.height;
}
void Helper::setdownrect(int num, IntRect& v)
{
	*(d + num - 1) = v;

	xd = v.width;
	yd = v.height;
}

void Helper::repeated(bool flag)
{
	repeat = flag;
}
void Helper::gamedimension(float** positionb)
{
	
	gamedim = positionb;

	gamewidth = positionb[0][0];
	gamelength = positionb[1][0];

}
void Helper::repeattime(float watch)
{
	//time = seconds(watch);
	repeatnum = gamewidth / watch;
	//helper = new Sprite[repeatnum];
	helperspeed = repeatnum;
	/*for (int i = 0; i < repeatnum; i++)
	{
	//helpers[i] = helper;
	/**(helpers + i).setTexture(texture);
	*(helpers + i).setTextureRect(intrect);
	*(helpers + i).setOrigin(x, y);*/

	//}
}
void Helper::repeatrandom(bool flag)
{
	random = flag;

	//helpers = new Sprite[repeatnum];
	/*if(random)
	helperspeed = rand() % 20;
	//for (int i = 0; i < repeatnum; i++)
	//{
	//	helpers[i] = helper;
	//	/**(helpers + i).setTexture(texture);
	//	*(helpers + i).setTextureRect(intrect);
	//	*(helpers + i).setOrigin(x, y);*/
	//}


}
void Helper::setrandom()
{
	if (random)
	{
		repeatnum = float(rand() % 20);
		helperspeed = repeatnum;
	}
}

void Helper::moveright()
{
	if (right > 0)
	{
		helper.setTextureRect(*(r + movecount%right));
		movecount++;
	}

	old = helper.getPosition();

	helper.setOrigin(xr / 2, yr / 2);

	helper.move(helperspeed, 0);

	update = helper.getPosition();

	gamedimension(gamedim);

	if (repeat)
	{
		if (helper.getPosition().x - xr / 2 > gamewidth)
		{
			helper.setPosition(Vector2f((-xr / 2), helper.getPosition().y));
		}
	}

	movright = true;
	movleft = false;
	movup = false;
	movdown = false;

}
void Helper::moveleft()
{
	if (left > 0)
	{
		helper.setTextureRect(*(l + movecount%left));
		movecount++;
	}

	old = helper.getPosition();

	helper.setOrigin(xl / 2, yl / 2);
	helper.move(-helperspeed, 0);

	update = helper.getPosition();

	gamedimension(gamedim);

	if (repeat)
	{
		if (helper.getPosition().x + xl / 2 < 0)
		{
			helper.setPosition(gamewidth + xl / 2, helper.getPosition().y);
		}
	}

	movright = false;
	movleft = true;
	movup = false;
	movdown = false;
}
void Helper::moveup()
{
	if (up > 1)
	{
		helper.setTextureRect(*(u + movecount%up));
		movecount++;
	}

	old = helper.getPosition();

	helper.setOrigin(xu / 2, yu / 2);

	helper.move(0, -helperspeed);

	update = helper.getPosition();

	gamedimension(gamedim);

	if (repeat)
	{
		if (helper.getPosition().y + yu / 2 < 0)
		{
			helper.setPosition(helper.getPosition().x, gamelength + yu / 2);
		}
	}

	movright = false;
	movleft = false;
	movup = true;
	movdown = false;

}
void Helper::movedown()
{
	if (down > 1)
	{
		helper.setTextureRect(*(d + movecount%down));
		movecount++;
	}

	old = helper.getPosition();

	helper.setOrigin(xd / 2, yd / 2);

	helper.move(0, helperspeed);

	update = helper.getPosition();

	gamedimension(gamedim);

	if (repeat)
	{
		if (helper.getPosition().y - yd / 2 >gamelength)
		{
			helper.setPosition(helper.getPosition().x, -yd / 2);
		}
	}

	movright = false;
	movleft = false;
	movup = false;
	movdown = true;
}

void Helper::speed(float f)
{
	helperspeed = f;

}
void Helper::settexture(Texture& texturep)
{
	texture = &texturep;
	helper.setTexture(*texture);
}
void Helper::setintrect(IntRect& intrectk)
{
	intrect = &intrectk;
	helper.setTextureRect(*intrect);
	x = intrectk.width;
	y = intrectk.height; 
	xl = x;
	xr = x;
	xu = x;
	xd = x;
	yl = y;
	yr = y;
	yu = y;
	yd = y;
	helper.setOrigin(x / 2, y / 2);
}
void Helper::setpos(Vector2f* positionb, Vector2f* difference)
{
	position = positionb;
	changeinpos = difference;

	positionofother->x = positionb->x + difference->x;
	positionofother->y = positionb->y + difference->y;
	
	helper.setPosition(*positionofother);
}

void Helper::rotate(float angle)
{
	helper.rotate(angle);
}

Vector2f* Helper::returnpos()
{
	position->x= helper.getPosition().x;
	position->y = helper.getPosition().y;


	return position;
}

Vector2f Helper::returnsize()
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

bool Helper::ifmove()
{
	if (old == update)
	{
		return false;
	}
	else return true;
}
Vector2f Helper::playermove()
{
	return update - old;
}

void Helper::scalefirst(Vector2f* positionb)
{
	if (!setinitialscale)
	{
		helper.scale(*positionb);
		setinitialscale = true;
		scalefactor= positionb;
		scalefactorx = positionb->x;
		scalefactory = positionb->y;
	}

	
}

void Helper::render(RenderWindow & window)
{
	window.draw(helper);
}

void Helper::scale(Vector2f* scalevalue)
{
	scalefactorx *= scalevalue->x;
	scalefactory *= scalevalue->y;

	//player.scale(Vector2f(1/ scalefactorx, 1/ scalefactory));
	helper.scale(Vector2f(scalefactorx, scalefactory));// (gamedim->y / 20) / y));

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
Vector2f* Helper::returnscale()
{
	return scalefactor;
}



