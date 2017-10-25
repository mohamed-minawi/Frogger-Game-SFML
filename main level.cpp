
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "button.h"
#include "player.h"
#include "Enemy.h"
#include "Helper.h"
#include "Obstacle.h"
#include "menu.h"
#include "Helper.h"
#include "Level.h"
using namespace std;
using namespace sf;

void main()
{
	float*	gamewidth;
	gamewidth = new float;
	*gamewidth = 1360;
	float*	gameheight;
	gameheight = new float;
	*gameheight = 700;

	Vector2f *gamedim;
	gamedim = &Vector2f(*gamewidth, *gameheight);

	float	largebuttonwidth = 167;
	float	largebuttonheight = 39;
	float	smallbuttonwidth = 40;
	float	smallbuttonheight = 40;
	
	Helper *frogtemp;
	frogtemp = new Helper;


	Texture animal;

	animal.loadFromFile("animals.jpeg.png");

	frogtemp->gamedimension(gamedim);
	frogtemp->settexture(animal);
	frogtemp->setintrect(IntRect(229, 235, 23, 20));

	Vector2f *frogposition;
	frogposition = new Vector2f;
	frogposition->x = *gamewidth / 2;
	frogposition->y = *gameheight *.95;

	frogtemp->setpos(frogposition);
	frogtemp->numofrtsprite(3);
	frogtemp->setrightrect(3, IntRect(230, 206, 22, 17));
	frogtemp->setrightrect(2, IntRect(262, 205, 24, 19));
	frogtemp->setrightrect(1, IntRect(198, 201, 24, 22));
	frogtemp->numofltsprite(3);
	frogtemp->setleftrect(3, IntRect(230, 174, 22, 17));
	frogtemp->setleftrect(1, IntRect(196, 169, 24, 22));
	frogtemp->setleftrect(2, IntRect(260, 173, 24, 19));
	frogtemp->numofupsprite(3);
	frogtemp->setuprect(3, IntRect(229, 235, 23, 20));
	frogtemp->setuprect(1, IntRect(262, 234, 21, 21));
	frogtemp->setuprect(2, IntRect(198, 232, 21, 24));
	frogtemp->numofdownsprite(3);
	frogtemp->setdownrect(3, IntRect(230, 142, 21, 17));
	frogtemp->setdownrect(1, IntRect(262, 141, 21, 19));
	frogtemp->setdownrect(2, IntRect(200, 138, 17, 19));


	RenderWindow window(VideoMode(*gamewidth, *gameheight, 32), "Mitcho buttons");

	Level one("level1.txt");
	one.setgamedim(gamedim);
	
	bool fullscreen=true;
	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			Vector2i mp;
			mp = Mouse::getPosition(window);
			if (event.type == sf::Event::Closed || event.key.code == Keyboard::Escape)
				window.close();
			if (event.key.code == Keyboard::F11)
			{
				if (fullscreen)
				{
					window.create(VideoMode(857, 642), "Mitcho Buttons");

					*gamewidth = window.getSize().x;
					*gameheight = window.getSize().y;

					*gamedim = Vector2f(*gamewidth, *gameheight);

					frogposition->x = *gamewidth / 2;
					frogposition->y = *gameheight *.95;

					fullscreen = false;
					one.levelscale(gamedim);
					frogtemp->scale(gamedim);

					/*helperposition[0][0]->y = gameheight*.15;
					helperposition[0][1]->y = gameheight*.25;
					helperposition[0][2]->y = gameheight*.25;
					helperposition[0][3]->y = gameheight*.35;
					helperposition[0][4]->y = gameheight*.35;
					helperposition[0][5]->y = gameheight*.35;

					for (int i = 0; i < helper.size(); i++)
					for (int j = 0; j < helper[i].size(); j++)
					{
						helper[i][j].scale(gamedim);
					}*/
					


				}

			}
		}
		window.clear();
		one.render(window);
		frogtemp->render(window);
		window.display();
	}

}