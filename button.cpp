#include "button.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

using namespace std;
using namespace sf;


button::button()
{
	hovers = false, magn = false, intrectt = false, intrecti = false;
}
void button::setsize(Vector2f g)
{
	buttonwidth = g.x;
	buttonheight = g.y;
}
void button::setdim(Vector2f* d)
{
	gameheight = new float;
	gamewidth = new float;

	*gameheight = (d->y);
	*gamewidth = (d->x);
}
void button::settexture(Texture& x)
{
	textureoriginal = &x;
	but.setTexture(*textureoriginal);

}
void button::settexture(Texture& x,IntRect y)
{
	textureoriginal = &x;
	intrectoringinal = y;
	but.setTexture(*textureoriginal);
	but.setTextureRect(intrectoringinal);
	intrecti = true;
}
void button::settexture(IntRect& x)
{
	intrectoringinal = x;
	but.setTextureRect(intrectoringinal);
	
}
void button::setcolor(Color x)
{
	but.setColor(x);
}
void button::setorigin()
{
	but.setOrigin(buttonwidth/2,buttonheight/2);
}
void button::settext(string x, int s,Color c)
{
	txt.setFont(font);
	txt.setString(x);
	
	charsize = s;
	FloatRect rect = txt.getGlobalBounds();
	int y = x.size();

	txt.setOrigin(y*charsize*0.325, charsize*0.8);

	txt.setPosition(but.getPosition().x, but.getPosition().y);
	txt.setCharacterSize(s);
	txt.setColor(c);
	
}

Vector2f* button::returnpos()
{
	/*Vector2f* x;
	Vector2f y;
	y = but.getPosition();
	x = &y;*/
	return position;
}
void button::setposition(Vector2f* pos)
{
	position = pos;
	but.setPosition(*position);
	sp = true;
}
void button::alignh(Vector2f* pos, float dif)
{
	difference = dif;
	position = pos;
	position->x += dif;
	but.setPosition(*position);
	ah = true;
}
void button::alignv(Vector2f* pos, float dif)
{
	difference = dif;
	position = pos;
	position->y += dif;
	but.setPosition(*position);
	av = true;
}
void button::loadfont(Font f)
{
	font = f;
}
void button::centerh(float y)
{
	difference = y;
	but.setPosition(*gamewidth / 2, difference);
	ch = true;
}
void button::centerv(float x)
{
	difference = x;
	but.setPosition(x, *gameheight / 2);
	cv = true;
}
void button::hover(bool z)
{
	hovers = z;
}
bool button::ifhover(Vector2i x)
{
	if (x.x > but.getPosition().x - buttonwidth / 2 && x.x<but.getPosition().x + buttonwidth / 2 && x.y>but.getPosition().y - buttonheight / 2 && x.y < but.getPosition().y + buttonheight / 2)
		return true;
	else return false;
}
void button::sethovertexture(IntRect& x, int y, int z)
{
	texturenew = textureoriginal;
	intrectnew=&x;
	xn = y;
	yn = z;
	intrectt = true;
}
void button::sethovertexture(Texture& x, IntRect& z, int y, int j)
{
	texturenew=&x;
	intrectnew = &z;
	xn = y;
	yn = j;
	intrectt = true;
}
void button::sethovertexture(Texture& x)
{
	texturenew = &x;
}
void button::hoverchange()
{
	but.setTexture(*texturenew);

	if (intrectt)
	{
		but.setTextureRect(*intrectnew);
		if (magn)
			but.setScale(1.1, 1.1);
	}
}
void button::magnify(bool flag)
{
	magn = flag;
}
void button::returntooriginal()
{
	if (intrecti)
	{
		but.setTexture(*textureoriginal);
		but.setTextureRect(intrectoringinal);

		if (magn)
	 but.setScale(1, 1);
	}
	else
		but.setTexture(*textureoriginal);
}
void button::render(RenderWindow& window)
{
	window.draw(but);
	window.draw(txt);

}
void button::setscale(Vector2f* gamedim)
{
	//but.setScale(xnew/xwidth, ynew/yheight);

	scalefactorx = *gamewidth / gamedim->x;
	scalefactory = *gameheight / gamedim->y;
	buttonwidth *= scalefactorx;
	buttonheight *= scalefactory;
	gameheight = & gamedim->y;
	gamewidth = &gamedim->x;
	//txt.setScale(xnew/xwidth, ynew/yheight);

	if (cv)
		centerv(difference);
	if (ch)
		centerh(difference);
	if (sp)
		setposition(position);
	if (av)
		alignv(position, difference);
	if (ah)
		alignh(position, difference);
	
	txt.setPosition(but.getPosition().x, but.getPosition().y);
}

/*void button::setscale(int xwidth, int yheight, int xnew, int ynew)
{
	//but.setScale(xnew/xwidth, ynew/yheight);

	buttonwidth *= xnew / xwidth;
	buttonheight *= ynew / yheight;
	gameheight = yheight;
	gamewidth = xwidth;
	//txt.setScale(xnew/xwidth, ynew/yheight);

	if (av)
		alignv(position, difference*ynew / yheight);
	if (ah)
		alignh(position, difference*xnew / xwidth);

	txt.setPosition(but.getPosition().x, but.getPosition().y);
}*/