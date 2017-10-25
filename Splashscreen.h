#ifndef SplashScreen_H
#define SplashScreen_H

#include <iostream>
#include <string>
#include "SFML\Graphics.hpp"

using namespace sf;
class SplashScreen
{
public:
	SplashScreen();
	//~SplashScreen();

	void numofpic(int);
	void settexture(Texture&);
	void loadcontent(int, IntRect&);
	void size(Vector2u& x);
	void screensize(int, int);
	void play(RenderWindow& window,float);
	void render(sf::RenderWindow& window);
	void update();
	void setlogo(Texture&);

protected:
private:
	//sf::Text text;
	//sf::Font font;
	//sf::Image image;
	Sprite splashscreen;
	int imgNum;
	Texture *p;
	IntRect *intrect;
	int gameheight, gamewidth;
	int count = 0;
	float scalefactorx, scalfactory;
	Clock clock;
	Sprite logo;
	bool logoflag = false;
	
};

#endif // SPLASHSCREEN_H
