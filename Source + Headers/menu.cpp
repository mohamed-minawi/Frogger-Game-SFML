#include "menu.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <vector>
using namespace sf;

menu::menu()
{
}
void menu::setbackground(Texture& t)
{
	background.setTexture(t);
	
	background.setPosition(0, 0);
}
void menu::setsubtitle(int i, string x, int s, Color c, Vector2f  pos)
{	
	Text sub;
	int y = x.size();
	position[i-1] = pos;
	charsize[i - 1] = s;
	sub.setOrigin(y*s*0.325, s*0.8);
	sub.setString(x);
	sub.setCharacterSize(s);
	sub.setColor(c);
	sub.setFont(font);
	sub.setPosition(*gamewidth / pos.x, *gameheight / pos.y);
	
	settext(sub, i);
}
void menu::settext(Text sub, int ind)
{
	subtitle[ind-1] = sub;
}
void menu::setfont(Font f)
{
	font = f;
}
void menu::setnumber(int numb)
{
	index = numb;
}
void menu::render(RenderWindow & window)
{
	window.draw(background);
	for (int i = 0; i < index; i++)
		window.draw(subtitle[i]);
}

void menu::setdim(Vector2f* dim)
{
	gameheight = new float;
	gamewidth = new float;

	gameheight = &(dim->y);
	gamewidth = &(dim->x);
}
void menu::setscale(Vector2f *gamedim)
{
	scalefactorx = *gamewidth / gamedim->x;
	scalefactory = *gameheight / gamedim->y;
	gameheight = &gamedim->y;
	gamewidth = &gamedim->x;
	background.scale(1/scalefactorx, 1/scalefactory);
	for (int i = 0; i < index; i++)
	{
	
		subtitle[i].setCharacterSize(charsize[i] / scalefactory);

		subtitle[i].setOrigin(subtitle[i].getString().getSize()*charsize[i] * 0.325, charsize[i] * 0.8);
		subtitle[i].setPosition(Vector2f(*gamewidth/position[i].x,*gameheight/position[i].y));
		
	}
}
