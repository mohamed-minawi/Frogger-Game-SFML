#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include "button.h"
#include "player.h"
#include "Enemy.h"
#include "Helper.h"
#include "Obstacle.h"
#include "menu.h"
//#/*include "Helper.h"
//#include "Obstacle.h*/

using namespace std;
using namespace sf;

IntRect largenormal(326, 1, 167, 39);
IntRect largehover(34, 1, 167, 39);
IntRect smallnormal(0, 2, 40, 40);
IntRect smallhover(78, 0, 40, 40);
IntRect smallpressed(148, 1, 40, 40);

//#define gamewidth 1360
//#define gameheight= 700
//#define largebuttonwidth= 167
//#define largebuttonheight= 39
//#define smallbuttonwidth= 40
//#define smallbuttonheight =40


void main()
{
	float*	gamewidth;
	gamewidth = new float;
	*gamewidth = 1360;
	float*	gameheight;
	gameheight = new float;
	*gameheight = 700;

	Vector2f *gamedim;
	gamedim= &Vector2f(*gamewidth, *gameheight);
	 
	float	largebuttonwidth = 167;
	float	largebuttonheight = 39;
	float	smallbuttonwidth = 40;
	float	smallbuttonheight = 40;
	 
	RenderWindow window(VideoMode(*gamewidth,* gameheight,32), "Mitcho buttons");
	
	Texture hometexture, largetexture, background, smalltexture;

	Font font, titlefont;

	bool homeflag = true, settingflag = false, storyflag = false, creditflag = false, highscoreflag = false, nameflag = false, charflag = false, singlemultiflag = false;

	button playbut, settingbut, quitbut, highscorebut, creditsbut, storybut, backbut, easy, medium, hard, on,off,single,multi;
	menu home, settingm,storymenu ,creditm,charm,namem,singmulti;
	Text inputname;
	string str;

	hometexture.loadFromFile("homepage1.png");
	smalltexture.loadFromFile("small.gif");
	largetexture.loadFromFile("buttons.png");
	background.loadFromFile("background.png");
	font.loadFromFile("zorque.ttf");
	titlefont.loadFromFile("KeepCalm-Medium.ttf");

	home.setbackground(hometexture);

	settingm.setbackground(background);
	settingm.setnumber(4);
	settingm.setfont(titlefont);
	settingm.setsubtitle(1, "Settings", 60, Color::Red, Vector2f(*gamewidth / 2, *gameheight / 10));
	settingm.setsubtitle(2, "Difficulty", 20, Color::Red, Vector2f(*gamewidth / 3.1, *gameheight / 4.5));
	settingm.setsubtitle(3, "Sound", 20, Color::Red, Vector2f(*gamewidth / 3.5, *gameheight / 2.5));
	settingm.setsubtitle(4, "Volume", 20, Color::Red, Vector2f(*gamewidth / 3.5, *gameheight / 1.75));

	storymenu.setbackground(background);
	storymenu.setfont(titlefont);
	storymenu.setnumber(2);
		
	singmulti.setbackground(background);
	singmulti.setfont(titlefont);
	singmulti.setnumber(1);
	singmulti.setsubtitle(1, "Please choose Single or Multiplayer", 35,Color::Red, Vector2f(Vector2f(*gamewidth / 2, *gameheight / 10)));

	creditm.setbackground(background);
	creditm.setfont(titlefont);
	creditm.setnumber(2);
	creditm.setsubtitle(1, "Credits", 60, Color::Red, Vector2f(*gamewidth / 2, *gameheight / 10));

	
	playbut.settexture(largetexture, largenormal);
	playbut.setdim(gamedim);
	playbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	playbut.setorigin();

	Vector2f* playbutposition;
	playbutposition = new Vector2f;
	playbutposition->x = *gamewidth / 9.5 + largebuttonwidth / 2;
	playbutposition->y = *gameheight / 4.65 + largebuttonheight / 2;

	playbut.setposition(playbutposition);
	playbut.settext("play", 25, Color::Black);
	playbut.loadfont(font);
	playbut.sethovertexture(largehover, 0, 0);
	playbut.hover(true);
	playbut.magnify(true);

	settingbut.settexture(largetexture, largenormal);
	settingbut.setdim(gamedim);
	settingbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	settingbut.setorigin();
	settingbut.alignv(playbutposition, largebuttonheight);
	settingbut.settext("Settings", 20, Color::Black);
	settingbut.loadfont(font);
	settingbut.sethovertexture(largehover, 0, 0);
	settingbut.hover(true);
	settingbut.magnify(true);

	storybut.settexture(largetexture, largenormal);
	storybut.setdim(gamedim);
	storybut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	storybut.setorigin();
	storybut.alignv((settingbut.returnpos()), largebuttonheight);
	storybut.settext("Story", 20, Color::Black);
	storybut.loadfont(font);
	storybut.sethovertexture(largehover, 0, 0);
	storybut.hover(true);
	storybut.magnify(true);

	highscorebut.settexture(largetexture, largenormal);
	highscorebut.setdim(gamedim);
	highscorebut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	highscorebut.setorigin();
	highscorebut.alignv(storybut.returnpos(), largebuttonheight);
	highscorebut.settext("Highscore", 20, Color::Black);
	highscorebut.loadfont(font);
	highscorebut.sethovertexture(largehover, 0, 0);
	highscorebut.hover(true);
	highscorebut.magnify(true);

	creditsbut.settexture(largetexture, largenormal);
	creditsbut.setdim(gamedim);
	creditsbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	creditsbut.setorigin();
	creditsbut.alignv(highscorebut.returnpos(), largebuttonheight);
	creditsbut.settext("Credits", 20, Color::Black);
	creditsbut.loadfont(font);
	creditsbut.sethovertexture(largehover, 0, 0);
	creditsbut.hover(true);
	creditsbut.magnify(true);

	quitbut.settexture(largetexture, largenormal);
	quitbut.setdim(gamedim);
	quitbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	quitbut.setorigin();
	quitbut.alignv(creditsbut.returnpos(), largebuttonheight);
	quitbut.settext("Quit", 20, Color::Black);
	quitbut.loadfont(font);
	quitbut.sethovertexture(largehover, 0, 0);
	quitbut.hover(true);
	quitbut.magnify(true);

	backbut.setdim(gamedim);
	backbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	backbut.settexture(largetexture, largenormal);
	backbut.setorigin();
	backbut.centerh(*gameheight / 1.125);
	backbut.loadfont(font);
	backbut.settext("Back", 25, Color::Black);
	backbut.sethovertexture(largehover, 0, 0);
	backbut.magnify(true);
	backbut.hover(true);

	easy.setdim(gamedim);
	easy.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	easy.settexture(smalltexture, smallnormal);
	easy.settexture(smallpressed);
	easy.setorigin();

	Vector2f* easyposition;
	easyposition = new Vector2f;
	easyposition->x = *gamewidth / 2.5;
	easyposition->y = *gameheight / 3.5;

	easy.setposition(easyposition);
	easy.loadfont(font);
	easy.settext("E", 25, Color::Black);
	easy.hover(true);
	easy.sethovertexture(smallhover, 0, 0);
	easy.magnify(true);

	medium.setdim(gamedim);
	medium.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	medium.settexture(smalltexture, smallnormal);
	medium.setorigin();
	medium.alignh(easy.returnpos(), 1.5*smallbuttonwidth);
	medium.loadfont(font);
	medium.settext("M", 25, Color::Black);
	medium.hover(true);
	medium.sethovertexture(smallhover, 0, 0);
	medium.magnify(true);

	hard.setdim(gamedim);
	hard.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	hard.settexture(smalltexture, smallnormal);
	hard.setorigin();
	hard.alignh(medium.returnpos(), 1.5*smallbuttonwidth);
	hard.loadfont(font);
	hard.settext("H", 25, Color::Black);
	hard.hover(true);
	hard.sethovertexture(smallhover, 0, 0);
	hard.magnify(true);

	on.setdim(gamedim);
	on.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	on.settexture(smalltexture, smallnormal);
	on.settexture(smallpressed);
	on.setorigin();

	Vector2f* onbutposition;
	onbutposition = new Vector2f;
	onbutposition->x = *gamewidth / 2.5;
	onbutposition->y = *gameheight / 2.1;

	on.setposition(onbutposition);
	on.loadfont(font);
	on.settext("On", 19, Color::Black);
	on.hover(true);
	on.sethovertexture(smallhover, 0, 0);
	on.magnify(true);

	off.setdim(gamedim);
	off.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	off.settexture(smalltexture, smallnormal);
	off.setorigin();
	off.alignh(on.returnpos(), 1.5*smallbuttonwidth);
	off.loadfont(font);
	off.settext("Off", 19, Color::Black);
	off.hover(true);
	off.sethovertexture(smallhover, 0, 0);
	off.magnify(true);

	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			Vector2i mp;
			mp = Mouse::getPosition(window);
			if (event.type == sf::Event::Closed || event.key.code == Keyboard::Escape)
				window.close();
			
			if (event.key.code == Keyboard::B)
			{
			
			}
			if (event.key.code == Keyboard::F11)
			{
				window.create(VideoMode(857, 642), "Mitcho Buttons");
				
				*gamewidth = window.getSize().x;
				*gameheight = window.getSize().y;

				home.setscale();
				settingm.setscale();
				storymenu.setscale();
				creditm.setscale();
				singmulti.setscale();

				gamedim = &Vector2f(*gamewidth, *gameheight);

				playbutposition->x = *gamewidth / 9.5 + largebuttonwidth / 2;
				playbutposition->y = *gameheight / 4.65 + largebuttonheight / 2;

				easyposition->x = *gamewidth / 2.5;
				easyposition->y = *gameheight / 3.5;


				onbutposition->x = *gamewidth / 2.5;
				onbutposition->y = *gameheight / 2.1;

				
				playbut.setscale(gamedim);
				settingbut.setscale(gamedim);
				storybut.setscale(gamedim);
				highscorebut.setscale(gamedim);
				quitbut.setscale(gamedim);
				creditsbut.setscale(gamedim);
				
				backbut.setscale(gamedim);
				easy.setscale(gamedim);
				medium.setscale(gamedim);
				hard.setscale(gamedim);
				on.setscale(gamedim);
				off.setscale(gamedim);


				
				/*playbut.setorigin();
				settingbut.setorigin();
				storybut.setorigin();
				highscorebut.setorigin();
				creditsbut.setorigin();
				quitbut.setorigin();
				backbut.setorigin();
				easy.setorigin();
				medium.setorigin();
				hard.setorigin();
				on.setorigin();
				off.setorigin();*/

				/*playbut.setposition(Vector2f(*gamewidth / 9.5 + largebuttonwidth / 2, *gameheight / 4.65 + largebuttonheight / 2));
				settingbut.alignv(playbut.returnpos(), largebuttonheight);
				storybut.alignv(settingbut.returnpos(), largebuttonheight);
				highscorebut.alignv(storybut.returnpos(), largebuttonheight);
				creditsbut.alignv(highscorebut.returnpos(), largebuttonheight);
				quitbut.alignv(creditsbut.returnpos(), largebuttonheight);
				backbut.centerh(*gameheight / 1.125);
				easy.setposition(Vector2f(*gamewidth / 2.5, *gameheight / 3.5));
				medium.alignh(Vector2f(easy.returnpos()), 1.5*smallbuttonwidth);
				hard.alignh(Vector2f(medium.returnpos()), 1.5*smallbuttonwidth);
				on.setposition(Vector2f(*gamewidth / 2.5, *gameheight / 2.1));
				off.alignh(Vector2f(on.returnpos()), 1.5*smallbuttonwidth);*/
				
			}
			if (homeflag)
			{
				if (playbut.ifhover(mp))
				{
					playbut.hoverchange();

				}
				else playbut.returntooriginal();


				if (settingbut.ifhover(mp))
				{
					settingbut.hoverchange();

				}
				else settingbut.returntooriginal();

				if (storybut.ifhover(mp))
				{
					storybut.hoverchange();

				}
				else storybut.returntooriginal();

				if (highscorebut.ifhover(mp))
				{
					highscorebut.hoverchange();

				}
				else highscorebut.returntooriginal();


				if (quitbut.ifhover(mp))
				{
					quitbut.hoverchange();

				}
				else quitbut.returntooriginal();


				if (creditsbut.ifhover(mp))
				{
					creditsbut.hoverchange();

				}
				else creditsbut.returntooriginal();
				
			}
			if (backbut.ifhover(mp))
			{
				backbut.hoverchange();

			}
			else backbut.returntooriginal();
			if (settingflag)
			{
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

				if (on.ifhover(mp))
				{
					on.hoverchange();

				}
				else on.returntooriginal();

				if (off.ifhover(mp))
				{
					off.hoverchange();

				}
				else off.returntooriginal();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				Vector2i ml = Mouse::getPosition(window);
				if (homeflag)
				{
					if (quitbut.ifhover(ml))
						window.close();
					if (settingbut.ifhover(ml))
					{
						settingflag = true;
						homeflag = false;
					}
					if (storybut.ifhover(ml))
					{
						storyflag = true;
						homeflag = false;
					}
					if (creditsbut.ifhover(ml))
					{
						creditflag = true;
						homeflag = false;
					}
					if (playbut.ifhover(ml))
					{
						singlemultiflag = true;
						homeflag = false;
					}
				}
				if (backbut.ifhover(ml))
				{
					settingflag = false;
					storyflag = false;
					highscoreflag = false;
					homeflag = true;
					creditflag = false;
					singlemultiflag = false;
				}
				if (settingflag)
				{
					if (easy.ifhover(ml))
					{
						easy.settexture(smallpressed);
						medium.settexture(smallnormal);
						hard.settexture(smallnormal);
					}

					if (medium.ifhover(ml))
					{
						easy.settexture(smallnormal);
						medium.settexture(smallpressed);
						hard.settexture(smallnormal);
					}

					if (hard.ifhover(ml))
					{
						easy.settexture(smallnormal);
						medium.settexture(smallnormal);
						hard.settexture(smallpressed);
					}
					if (on.ifhover(ml))
					{
						off.settexture(smallnormal);
						on.settexture(smallpressed);
					}
					if (off.ifhover(ml))
					{
						off.settexture(smallpressed);
						on.settexture(smallnormal);
					}
				}
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == 8 && str.size() != 0)
					{
						str.erase(str.size() - 1);
						inputname.setString(str);
					}
					else if (event.text.unicode < 128 && event.text.unicode>65)
					{
						str += static_cast<char>(event.text.unicode);
						inputname.setString(str);

						if (str.length() > 0)
							inputname.move(-6.5, 0);
					}


					if (Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && str.length() > 0)
						inputname.move(6.5, 0);

					if (Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						//namepg = false;
						//gamestart = true;

					}
				}
			}
			
			}
			window.clear(Color::Green);
			if (homeflag &&!settingflag &&!storyflag &&!highscoreflag &&!creditflag&&!singlemultiflag)
			{
				home.render(window);
				playbut.render(window);
				settingbut.render(window);
				storybut.render(window);
				highscorebut.render(window);
				quitbut.render(window);
				creditsbut.render(window);
			}
			if (!homeflag &&settingflag &&!storyflag &&!highscoreflag &&!creditflag&&!singlemultiflag)
			{
				settingm.render(window);
				backbut.render(window);
				easy.render(window);
				medium.render(window);
				hard.render(window);
				on.render(window);
				off.render(window);
			}
			if (storyflag&&!homeflag &&!settingflag &&!highscoreflag &&!creditflag&&!singlemultiflag)
			{
				storymenu.render(window);
				backbut.render(window);
			}
			if (!storyflag&&!homeflag &&!settingflag &&!highscoreflag &&creditflag&&!singlemultiflag)
			{
				creditm.render(window);
				backbut.render(window);
			}
			if (singlemultiflag&&!storyflag&&!homeflag &&!settingflag &&!highscoreflag &&!creditflag )
			{
				singmulti.render(window);
				backbut.render(window);
			}
			window.display();

		}
	}