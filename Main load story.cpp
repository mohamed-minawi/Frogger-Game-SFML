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

IntRect loadintrect[7];


void main()
{
	RenderWindow window(VideoMode(gamewidth, gameheight), "Mitcho buttons");
	Texture loadimg, logo;

	loadimg.loadFromFile("Story.png");

	loadimg.setSmooth(true);
	loadimg.setRepeated(true);

	logo.loadFromFile("Drawing.png");

	SplashScreen load;
	loadint();
	load.numofpic(7);
	load.settexture(loadimg);
	for (int i = 0; i < 7; i++)
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

			window.display();

			window.clear();
			if (loadflag)
			{
				load.play(window, 5);
				//loadflag = false;
			}
			//	window.draw(k);
			window.display();

		}
	}
}
void loadint()
{
	loadintrect[0] = IntRect(1, 1, 223, 209);
	loadintrect[1] = IntRect(225, 1, 224, 209);
	loadintrect[2] = IntRect(1, 211, 223, 210);

	loadintrect[3] = IntRect(1, 422, 223, 209);
	loadintrect[4] = IntRect(225, 211,224, 210);
	loadintrect[5] = IntRect(450, 1, 224, 209);

	loadintrect[6] = IntRect(450, 211, 223, 210);
	/*loadintrect[7] = IntRect(345, 414, 331, 195);
	loadintrect[8] = IntRect(686, 414, 331, 195);

	loadintrect[9] = IntRect(5, 619, 331, 195);
	loadintrect[10] = IntRect(345, 619, 331, 195);
	loadintrect[11] = IntRect(686, 619, 331, 195);

	loadintrect[12] = IntRect(5, 824, 331, 195);
*/
}
