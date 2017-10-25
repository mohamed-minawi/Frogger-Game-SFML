#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include "Splashscreen.h"
#include "Helper.h"
#include "Obstacle.h"
#include "player.h"
#include "button.h"
#include "menu.h"

using namespace std;
using namespace sf;

void loadint();

IntRect n(150, 143, 105, 40);
IntRect h(264, 144, 105, 40);
IntRect pressed(131, 195, 51, 51);
IntRect hover(186, 195, 51, 51);
IntRect initial(239, 195, 51, 51);
#define gamewidth 857
#define gameheight 642
#define buttonwidth 105
#define buttonheight 40

IntRect loadintrect[13];


void main()
{
	RenderWindow window(VideoMode(gamewidth, gameheight), "Mitcho buttons");
	Texture loadimg, logo;

	loadimg.loadFromFile("Kermit.png");

	loadimg.setSmooth(true);
	loadimg.setRepeated(true);

	logo.loadFromFile("Drawing.png");

	SplashScreen load;
	loadint();
	load.numofpic(13);
	load.settexture(loadimg);
	for (int i = 0; i < 13; i++)
	{
		load.loadcontent(i + 1, loadintrect[i]);
	}
	Vector2u j(loadintrect[0].width, loadintrect[0].height);
	load.screensize(gamewidth, gameheight);
	load.size(j);
	load.setlogo(logo);

	bool loadflag = true;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			Vector2i mp;
			mp = Mouse::getPosition(window);
			if (event.type == sf::Event::Closed || event.key.code == Keyboard::Escape)
				window.close();
			/*if (event.type == Event::MouseButtonPressed)
			{
			Vector2i ml = Mouse::getPosition(window);
			if (settingbut.ifhover(ml))
			{
			homeflag = false;
			setflag = true;
			}
			}
			if (play.ifhover(mp))
			{
			play.hoverchange();
			}
			else play.returntooriginal();

			if (settingbut.ifhover(mp))
			{
			settingbut.hoverchange();
			}
			else settingbut.returntooriginal();

			if (easy.ifhover(mp))
			{
			easy.hoverchange();
			}
			else easy.returntooriginal();

			if (medium.ifhover(mp))
			{
			medium.hoverchange();
			}
			else medium.returntooriginal();
			if (hard.ifhover(mp))
			{
			hard.hoverchange();
			}
			else hard.returntooriginal();

			if (helpbut.ifhover(mp))
			{
			helpbut.hoverchange();
			}
			else helpbut.returntooriginal();


			}
			if (event.type == Event::MouseButtonPressed)
			{
			Vector2i ml = Mouse::getPosition(window);

			if (settingbut.ifhover(ml))
			{
			homeflag = false;
			setflag = true;
			}

			if (easy.ifhover(ml))
			{
			easy.settexture( pressed);
			medium.settexture( initial);
			hard.settexture( initial);
			}

			if (medium.ifhover(ml))
			{
			easy.settexture( initial);
			medium.settexture( pressed);
			hard.settexture( initial);
			}

			if (hard.ifhover(ml))
			{
			easy.settexture(initial);
			medium.settexture(initial);
			hard.settexture(pressed);
			}

			}*/

			/*
			log.moveright();
			if (movechange.ifmet(frog, log))
			{
			movechange.playermovewithhelper(frog, log);
			}

			if (frog.returnpos().x > gamewidth)
			frog.setpos(Vector2f(0, gameheight / 2 + 5));

			frog.moveright();*/

			window.clear();
			/*if (homeflag &&!setflag)
			{
			home.render(window);
			play.render(window);
			settingbut.render(window);
			helpbut.render(window);
			}
			if (setflag &&!homeflag)
			{
			settingm.render(window);
			easy.render(window);
			medium.render(window);
			hard.render(window);
			}

			log.render(window);
			frog.render(window);*/

			window.display();

			window.clear();
			if (loadflag)
			{
				load.play(window, 0.2);
				//loadflag = false;
			}
			//	window.draw(k);
			window.display();

		}
	}
}
void loadint()
{
	loadintrect[0] = IntRect(5, 5, 331, 195);
	loadintrect[1] = IntRect(345, 5, 331, 195);
	loadintrect[2] = IntRect(686, 5, 331, 195);

	loadintrect[3] = IntRect(5, 209, 331, 195);
	loadintrect[4] = IntRect(345, 209, 331, 195);
	loadintrect[5] = IntRect(686, 209, 331, 195);

	loadintrect[6] = IntRect(5, 414, 331, 195);
	loadintrect[7] = IntRect(345, 414, 331, 195);
	loadintrect[8] = IntRect(686, 414, 331, 195);

	loadintrect[9] = IntRect(5, 619, 331, 195);
	loadintrect[10] = IntRect(345, 619, 331, 195);
	loadintrect[11] = IntRect(686, 619, 331, 195);

	loadintrect[12] = IntRect(5, 824, 331, 195);

}
