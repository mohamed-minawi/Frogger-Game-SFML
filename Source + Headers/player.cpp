#include "player.h"
#include "SFML\Graphics.hpp"
#include <iostream>
using namespace sf;
using namespace std;


	Player::Player()
	{
		movecount = 0;
		playerspeed = 20;
	//	player.setTexture(*texture);
	//	player.setTextureRect(*intrect);
	//	player.setPosition(position);


	}

	void Player::numofrtsprite(int rt)
	{
		r = new IntRect[rt];
		right = rt;
	}
	void Player::numofltsprite(int lt)
	{
		l = new IntRect[lt];
		left = lt;
	}
	void Player::numofupsprite(int p)
	{
		u = new IntRect[p];
		up = p;
	}
	void Player::numofdownsprite(int dn)
	{
		d = new IntRect[dn];
		down = dn;
	}

	void Player::setrightrect(int num, IntRect& v)
	{
		r[num - 1] = v;

		xr = v.width;
		yr = v.height;
	}
	void Player::setleftrect(int num, IntRect& v)
	{
		l[num - 1] = v;

		xl = v.width;
		yl = v.height;
	}
	void Player::setuprect(int num, IntRect& v)
	{
		u[num - 1] = v;

		xu = v.width;
		yu = v.height;
	}
	void Player::setdownrect(int num, IntRect& v)
	{
		d[num - 1] = v;

		xd = v.width;
		yd = v.height;
	}

	void Player::speed(float f)
	{
		playerspeed = f;
		//cout << playerspeed << endl;

	}

	void Player::moveright()
	{
		if (right > 0)
		{
			player.setTextureRect(*(r + movecount%right));
			movecount++;
		}
		player.setOrigin(xr / 2, yr / 2);
		player.move(playerspeed, 0);

		animationCounter++;
		direction = 0;
	}
	void Player::moveleft()
	{
		if (left > 0)
		{
			player.setTextureRect(*(l + movecount%left));
			movecount++;
		}
		player.setOrigin(xl / 2, yl / 2);
		player.move(-playerspeed, 0);

		animationCounter ++;
		direction = 1;
	}
	void Player::moveup()
	{
		if (up > 0)
		{
			player.setTextureRect(*(u + movecount%up));
			movecount++;
		}
		player.setOrigin(xu / 2, yu / 2);
		player.move(0,-playerspeed);

		animationCounter++;
		direction = 2;
	}
	void Player::movedown()
	{
		if (down > 0)
		{
			player.setTextureRect(*(d + movecount%down));
			movecount++;
		}
		player.setOrigin(xd / 2, yd / 2);
		player.move(0, playerspeed);

		animationCounter++;
		direction = 3;
	}
	void Player::move(Vector2f& v)
	{
		player.move(v);
	}
	
	void Player::settexture(Texture& texturep)
	{
		texture = &texturep;
		player.setTexture(*texture);
	}

	void Player::setintrect(IntRect& intrectp)
	{
		intrect = &intrectp;
		player.setTextureRect(*intrect);
		x = intrectp.width;
		y = intrectp.height;

		player.setOrigin(x*scalefactorx / 2, y*scalefactory / 2);

		if (!setinitialscale)
		{
			player.scale(Vector2f((gamedim->y / 20) / y, (gamedim->y / 20) / y));
			setinitialscale = true;
		}
	}

	void Player::update(int numofiteration)
	{
		if (animationCounter<numofiteration)
			switch (direction)
			{
			case 0: {
						//animationCounter++;
						moveright();
			}
				break;
			case 1: {
						//animationCounter++;
						moveleft();
			}
				break;
			case 2: {
					//	animationCounter++;
						moveup();
			}
				break;
			case 3: {
						//animationCounter++;
						movedown();
			}
				break;
			}
		else animationCounter = 0;
	}
	
	void Player::setpos( Vector2f* positionb)
	{
		position = positionb;
		player.setPosition(*position);
		//player.scale(Vector2f((gamedim->y / 20) / y, (gamedim->y / 20) / y));
	}

	void Player::gamedimension(Vector2f* positionb)
	{
		gamedim = new Vector2f;
		gamedim->x= positionb->x;
		gamedim->y = positionb->y;
		
	}
	

	void Player::scale(Vector2f* positionb)
	{
		scalefactorx = positionb->x / gamedim->x;
		scalefactory = positionb->y / gamedim->y;
		gamedim->y = positionb->y;
		gamedim->x = positionb->x;
		
		//player.scale(Vector2f(1/ scalefactorx, 1/ scalefactory));
		player.scale(Vector2f(scalefactorx, scalefactory));// (gamedim->y / 20) / y));

		x *= scalefactorx;
		xl *= scalefactorx;
		xr *= scalefactorx;
		xu *= scalefactorx;
		xd *= scalefactorx;
		yl *= scalefactory;
		yr *= scalefactory;
		yu *= scalefactory;
		yd *= scalefactory;
		y *= scalefactory;

		setpos(position);
	}
		
	Vector2f* Player::returnpos()
	{
		position->x = player.getPosition().x;
		position->y = player.getPosition().y;


		return position;
	}

	FloatRect Player::returnsize()
	{
		return	player.getLocalBounds();
	}
		
	void Player::render(RenderWindow& window)
	{
		window.draw(player);
	}
