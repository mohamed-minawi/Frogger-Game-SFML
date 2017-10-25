#include "SplashScreen.h"
#include <iostream>
using std::cout;
using namespace sf;

SplashScreen::SplashScreen()
{
	//ctor
	count = 0;
	imgNum = 1;
}

///SplashScreen::~SplashScreen()
//{
//	//dtor
//
//	delete []intrect;
//	intrect = NULL;
//	
//	/*delete p;
//	p = NULL;*/
//}/

void SplashScreen::numofpic(int v)
{
	imgNum = v;
	intrect = new IntRect[imgNum];
}
void SplashScreen::screensize(int w, int h)
{
	gamewidth = w;
	gameheight = h;
}
void SplashScreen::size(Vector2u& x)
{

	scalefactorx = float(gamewidth) / (x.x);
	scalfactory = float(gameheight) /(x.y);

	splashscreen.setOrigin(x.x/2,x.y/2);

	splashscreen.setPosition(gamewidth / 2, gameheight * 15 / 32);

	splashscreen.setScale(1.75, 1.75);
}

void SplashScreen::settexture(Texture& texture)
{
	p = &texture;
	splashscreen.setTexture(texture);
	
}
void SplashScreen::loadcontent(int numofe, IntRect& sub)
{
	*(intrect + numofe - 1) = sub;
}
void SplashScreen::setlogo(Texture& texture)
{
	logo.setTexture(texture);
	//logo.setTextureRect(intrect);
	//logo.setOrigin(texture / 2, intrect.height / 2);
	logo.setOrigin(788/2, 160/2);
	logo.setPosition(gamewidth / 2, gameheight * 7 / 8); 

	logoflag = true;
}

void SplashScreen::play(RenderWindow& window, float  x)
{

	while (count<imgNum)

	if (clock.getElapsedTime().asSeconds()>x)
	{
		clock.restart();
		update();
		//std::cout << clock.getElapsedTime().asSeconds();
		/*if (clock.getElapsedTime().asSeconds() > .2)
		{
			clock.restart();*/
		window.clear(Color::White);

		window.draw(splashscreen);

		if (logoflag)
		window.draw(logo);

	//	}

	window.display();	
	}

	count = 0;
}
void SplashScreen::update()
{
	
	//if (count<imgNum)
	splashscreen.setTextureRect(*(intrect+count%imgNum));
	count++;

	/*}*/


}
void SplashScreen::render(sf::RenderWindow& window)
{
	update();
	window.draw(splashscreen);
}