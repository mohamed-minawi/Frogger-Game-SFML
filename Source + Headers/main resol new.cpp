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
#include "Level.h"


using namespace std;
using namespace sf;

IntRect largenormal(326, 1, 167, 39);
IntRect largehover(34, 1, 167, 39);
IntRect smallnormal(0, 2, 40, 40);
IntRect smallhover(78, 0, 40, 40);
IntRect smallpressed(148, 1, 40, 40);
IntRect imaginary(118, 27, 21, 19);
IntRect frogpos(262, 141, 21, 19);
float *gamewidth;
float *gameheight;

Texture hometexture, largetexture, background, smalltexture;

Font font, titlefont;

bool homeflag = true, settingflag = false, storyflag = false, creditflag = false, highscoreflag = false, nameflag = false, singlemultiflag = false, charchosen = false, namechosen = false, m = false, nextflag = false;

button playbut, settingbut, quitbut, highscorebut, creditsbut, storybut, backbut, easy, medium, hard, on, off, singlebut, multiplayerbut, nextbut;
menu home, settingm, storymenu, creditm, charm, namem, singmulti, singlem, multim;
Text inputname;
string str;
int counter;
Texture frogtexture[5];
vector<Player> frogtempvec;

vector<button> buttonvectotr;
button*  buttonpointer;

Vector2f *dimensions;
float	largebuttonwidth = 167;
float	largebuttonheight = 39;
float	smallbuttonwidth = 40;
float	smallbuttonheight = 40;
Vector2f image = Vector2f(21.0, 19.0);
Vector2f* easyposition;
Vector2f* singlebutpos;
Vector2f* playbutposition;
Vector2f* onbutposition;
Vector2f* newbutposition;
Vector2f* gamebuttonpos;
Vector2f* nextbutposition;
bool animation = false;

Vector2f *oldgamedim;

#define buttonwidth 105
#define buttonheight 40
Texture *carpicpointer;
bool keypressed = false, keypressed2 = false;
int animationcounter=0, animationcounter2=0, levelcount=1;
float enemyspeedfactor = 1, helperspeedfactor = 1, playerspeedfactor=1;
int lives = 7, lives2=7;
Vector2f* helperposition, **helperchange, *enemyposition, **enemychange;
Vector2f *scalefactor;
float **gamedim;
View view1, view2;
Clock skullclock;
Level one("level1.txt");


struct arraypos
{
	int i;
	int j;

	arraypos(int l, int k)
	{
		i = l;
		j = k;
	};
};

vector<Player> frog;
vector<vector<Enemy>>  enemy;
vector<vector<Helper>> helper;
vector<vector<float>>  speed;
vector<vector<vector<arraypos>>> direction;
vector<IntRect> waterpos;
//vector<vector<Vector2f*>> helperposition;

Vector2f *frogposition;

void handlelevels(Clock&);

void setlevel1();
void setlevel1resolution(RenderWindow&, Level&);
void setscale(RenderWindow&);
void loader();
void renderer(RenderWindow&);

void main()
{
	int animationcounter = 0, countswitch = 0;
	Clock clock;
	gamewidth = new float;
	*gamewidth = 1360;

	gameheight = new float;
	*gameheight = 700;

	dimensions = &Vector2f(*gamewidth, *gameheight);

	RenderWindow window(VideoMode(*gamewidth, *gameheight, 32), "Mitcho buttons", Style::Fullscreen);

	loader();

	Texture hometexture,buttexture, gametext;

	frog.reserve(2);
	scalefactor = new Vector2f;
	scalefactor->x = 1;
	scalefactor->y = 1;

	gamedim = new float*[2];


	*gamedim = gamewidth;
	*(gamedim+1) = gameheight;

	Texture animal;

	animal.loadFromFile("animals.jpeg.png");

	Player *frogtemp;

	frogtemp = new Player;

	Vector2f *gamedi;
	gamedi = new Vector2f;
	gamedi->x = gamedim[0][0];
	gamedi->y = gamedim[1][0];

	frogtemp->gamedimension(gamedi);
	frogtemp->settexture(animal);
	frogtemp->setintrect(IntRect(229, 235, 23, 20));

	
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

	frog.push_back(*frogtemp);

	///////////////////////////
	//frog.push_back(*frogtemp);


	///Vector2f((*gamedim->y / 10) / y, (*gamedim->y / 20) / y)
	///////////////////////

	delete frogtemp;
	frogtemp = NULL;

	vector<float> speedtemp;

	speedtemp.push_back((*gameheight*.15));
	///////////////////////////
	//speedtemp.push_back( * gameheight*.15);
	///////////////////////////
	speed.push_back(speedtemp);

	speedtemp.clear();

	Texture carpic;
	carpic.loadFromFile("Car.png");
	
	carpicpointer = &carpic;

	view1.setViewport(FloatRect(0, 0, .5, 1));
	view1.setSize(*gamewidth / 2, *gameheight);

	view2.setViewport(FloatRect(.5, 0, .5, 1));
	view2.setSize(*gamewidth / 2, *gameheight);

	Vector2f position(*gamewidth / 2, *gameheight / 2), position2(position);

	view1.setCenter(*gamewidth / 2, *gameheight / 2);
	view2.setCenter(*gamewidth / 2, *gameheight / 2);
	
	oldgamedim = new Vector2f;

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;

	setlevel1();

	float **fulldim;

	fulldim = new float*[2];

	fulldim[0] = new float;
	fulldim[1] = new float;
	fulldim[0][0] = 1360;
	fulldim[1][0] = 770;

	Vector2f *fulld;

	fulld = new Vector2f;
	fulld->x = 1360;
	fulld->y = 770;
	
	one.setgamedim(fulld);
	frog[0].gamedimension(fulld);
	frog[1].gamedimension(fulld);

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;

	window.create(VideoMode(800 , 500), "Mitcho Buttons");

	setlevel1resolution( window,  one);

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
				window.create(VideoMode(850, 650), "Mitcho Buttons");
				setscale(window);

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
			if (singlemultiflag)
			{
				if (singlebut.ifhover(mp))
				{
					singlebut.hoverchange();

				}
				else singlebut.returntooriginal();
				if (multiplayerbut.ifhover(mp))
				{
					multiplayerbut.hoverchange();

				}
				else multiplayerbut.returntooriginal();

			}
			if (nameflag)
			{
				if (m &&counter == 0)
				{
					namem.setsubtitle(1, "Enter player one name", 22, Color::Red, Vector2f(2.1, 10));
					namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
				}
				if (m &&counter == 1)
				{
					namem.setsubtitle(1, "Enter player two name", 22, Color::Red, Vector2f(2.1, 10));
					namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
					counter = 0;
					namechosen = false;
				}
				if (!m)
				{
					namem.setsubtitle(1, "Enter your name", 22, Color::Red, Vector2f(2.1, 10));
					namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
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
						namechosen = true;

					}
				}
				if (!m)
				{
					if (nextbut.ifhover(mp))
					{
						nextbut.hoverchange();

					}
					else nextbut.returntooriginal();
				}
				if (m&&charchosen&&namechosen)
				{
					if (nextbut.ifhover(mp))
					{
						nextbut.hoverchange();

					}
					else nextbut.returntooriginal();
				}
				if (clock.getElapsedTime().asSeconds() > .1)
				{
					clock.restart();

					if (buttonvectotr[0].ifhover(mp))
					{
						if (animationcounter < 3 && animation)
						{
							frogtempvec[0].update(3);
							animationcounter++;
						}
						else
						{
							animationcounter = 0;

							if (animation)
								animation = false;
						}

						if (animationcounter == 0)
							switch (countswitch % 4)
						{
							case 0:
							{
									  frogtempvec[0].speed(0);
									  frogtempvec[0].moveright();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 1:
							{
									  frogtempvec[0].speed(0);
									  frogtempvec[0].moveleft();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 2:
							{
									  frogtempvec[0].speed(0);
									  frogtempvec[0].moveup();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 3:
							{
									  frogtempvec[0].speed(0);
									  frogtempvec[0].movedown();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
						}



					}
					else frogtempvec[0].setintrect(IntRect(229, 235, 23, 20));

					if (buttonvectotr[1].ifhover(mp))
					{
						if (animationcounter < 3 && animation)
						{
							frogtempvec[1].update(3);
							animationcounter++;
						}
						else
						{
							animationcounter = 0;

							if (animation)
								animation = false;
						}

						if (animationcounter == 0)
							switch (countswitch % 4)
						{
							case 0:
							{
									  frogtempvec[1].speed(0);
									  frogtempvec[1].moveright();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 1:
							{
									  frogtempvec[1].speed(0);
									  frogtempvec[1].moveleft();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 2:
							{
									  frogtempvec[1].speed(0);
									  frogtempvec[1].moveup();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 3:
							{
									  frogtempvec[1].speed(0);
									  frogtempvec[1].movedown();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
						}



					}
					else frogtempvec[1].setintrect(IntRect(229, 235, 23, 20));

					if (buttonvectotr[2].ifhover(mp))
					{
						if (animationcounter < 3 && animation)
						{
							frogtempvec[2].update(3);
							animationcounter++;
						}
						else
						{
							animationcounter = 0;

							if (animation)
								animation = false;
						}

						if (animationcounter == 0)
							switch (countswitch % 4)
						{
							case 0:
							{
									  frogtempvec[2].speed(0);
									  frogtempvec[2].moveright();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 1:
							{
									  frogtempvec[2].speed(0);
									  frogtempvec[2].moveleft();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 2:
							{
									  frogtempvec[2].speed(0);
									  frogtempvec[2].moveup();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 3:
							{
									  frogtempvec[2].speed(0);
									  frogtempvec[2].movedown();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
						}



					}
					else frogtempvec[2].setintrect(IntRect(229, 235, 23, 20));

					if (buttonvectotr[3].ifhover(mp))
					{
						if (animationcounter < 3 && animation)
						{
							frogtempvec[3].update(3);
							animationcounter++;
						}
						else
						{
							animationcounter = 0;

							if (animation)
								animation = false;
						}

						if (animationcounter == 0)
							switch (countswitch % 4)
						{
							case 0:
							{
									  frogtempvec[3].speed(0);
									  frogtempvec[3].moveright();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 1:
							{
									  frogtempvec[3].speed(0);
									  frogtempvec[3].moveleft();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 2:
							{
									  frogtempvec[3].speed(0);
									  frogtempvec[3].moveup();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 3:
							{
									  frogtempvec[3].speed(0);
									  frogtempvec[3].movedown();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
						}



					}
					else frogtempvec[3].setintrect(IntRect(229, 235, 23, 20));

					if (buttonvectotr[4].ifhover(mp))
					{
						if (animationcounter < 3 && animation)
						{
							frogtempvec[4].update(3);
							animationcounter++;
						}
						else
						{
							animationcounter = 0;

							if (animation)
								animation = false;
						}

						if (animationcounter == 0)
							switch (countswitch % 4)
						{
							case 0:
							{
									  frogtempvec[4].speed(0);
									  frogtempvec[4].moveright();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 1:
							{
									  frogtempvec[4].speed(0);
									  frogtempvec[4].moveleft();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 2:
							{
									  frogtempvec[4].speed(0);
									  frogtempvec[4].moveup();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
							case 3:
							{
									  frogtempvec[4].speed(0);
									  frogtempvec[4].movedown();
									  animationcounter++;
									  countswitch++;

									  animation = true;
							}
								break;
						}



					}
					else frogtempvec[4].setintrect(IntRect(229, 235, 23, 20));
				}
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

					}
					if (storybut.ifhover(ml))
					{
						storyflag = true;

					}
					if (creditsbut.ifhover(ml))
					{
						creditflag = true;

					}
					if (playbut.ifhover(ml))
					{
						singlemultiflag = true;
						homeflag = false;

					}

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
					if (backbut.ifhover(ml))
					{
						settingflag = false;

					}

				}
				if (storyflag)
				{
					if (backbut.ifhover(ml))
					{
						storyflag = false;

					}
				}
				if (singlemultiflag)
				{
					if (singlebut.ifhover(ml))
					{
						nameflag = true;
						singlemultiflag = false;
						homeflag = false;
					}

					if (multiplayerbut.ifhover(ml))
					{
						nameflag = true;
						homeflag = false;
						m = true;
					}
					if (backbut.ifhover(ml))
					{
						singlemultiflag = false;
						homeflag = true;
					}
				}
				if (creditflag)
				{
					if (backbut.ifhover(ml))
					{
						creditflag = false;

					}
				}
				if (nameflag)
				{
					if (backbut.ifhover(ml))
					{
						nameflag = false;
						singlemultiflag = true;
						m = false;
						counter = 0;
					}
					if (buttonvectotr[0].ifhover(ml))
					{
						charchosen = true;

					}
					if (buttonvectotr[1].ifhover(ml))
					{
						charchosen = true;
					}
					if (buttonvectotr[2].ifhover(ml))
					{
						charchosen = true;
					}
					if (buttonvectotr[3].ifhover(ml))
					{
						charchosen = true;
					}
					if (buttonvectotr[4].ifhover(ml))
					{
						charchosen = true;
					}
				}
			}

		}

		handlelevels(clock);

		if (frog.size()>1)
		{
			if (frog[0].returnpos()->x >= view2.getSize().x / 2 && frog[0].returnpos()->x <= 3 * *gamewidth / 4)
				position.x = frog[0].returnpos()->x;

			if (frog[1].returnpos()->x >= view1.getSize().x / 2 && frog[1].returnpos()->x <= 3 * *gamewidth / 4)
				position2.x = frog[1].returnpos()->x;

			view1.setCenter(position2);
			view2.setCenter(position);
		}

		renderer(window);
	}
}

void loader()
{

	smalltexture.loadFromFile("small.gif");
	largetexture.loadFromFile("buttons.png");
	background.loadFromFile("background.png");
	font.loadFromFile("zorque.ttf");
	titlefont.loadFromFile("KeepCalm-Medium.ttf");

	hometexture.loadFromFile("homepage1.png");
	frogtexture[0].loadFromFile("animals.jpeg.png");
	frogtexture[1].loadFromFile("orange1.png");
	frogtexture[2].loadFromFile("purple1.png");
	frogtexture[3].loadFromFile("red1.png");
	frogtexture[4].loadFromFile("blue1.png");

	home.setbackground(hometexture);
	home.setdim(dimensions);

	settingm.setbackground(background);
	settingm.setnumber(4);
	settingm.setfont(titlefont);
	settingm.setdim(dimensions);
	settingm.setsubtitle(1, "Settings", 60, Color::Red, Vector2f(2, 10));
	settingm.setsubtitle(2, "Difficulty", 20, Color::Red, Vector2f(3.1, 4.5));
	settingm.setsubtitle(3, "Sound", 20, Color::Red, Vector2f(3.5, 2.5));
	settingm.setsubtitle(4, "Volume", 20, Color::Red, Vector2f(3.5, 1.75));

	storymenu.setbackground(background);
	storymenu.setfont(titlefont);
	storymenu.setnumber(2);
	storymenu.setdim(dimensions);

	singmulti.setbackground(background);
	singmulti.setfont(titlefont);
	singmulti.setnumber(1);
	singmulti.setdim(dimensions);
	singmulti.setsubtitle(1, "Single or Multiplayer", 25, Color::Red, Vector2f(2, 10));


	namem.setbackground(background);
	namem.setfont(titlefont);
	namem.setdim(dimensions);
	namem.setnumber(2);
	namem.setsubtitle(1, "Enter your name", 22, Color::Red, Vector2f(2.1, 10));
	namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));

	inputname.setFont(titlefont);
	inputname.setColor(Color::Black);
	inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
	inputname.setCharacterSize(12);

	creditm.setbackground(background);
	creditm.setfont(titlefont);
	creditm.setnumber(2);
	creditm.setdim(dimensions);
	creditm.setsubtitle(1, "Credits", 60, Color::Red, Vector2f(2, 10));

	nextbutposition = new Vector2f;
	nextbutposition->x = *gamewidth / 1.6;
	nextbutposition->y = *gameheight / 1.25;

	nextbut.settexture(largetexture, largenormal);
	nextbut.setdim(dimensions);
	nextbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	nextbut.setorigin();
	nextbut.setposition(nextbutposition);
	nextbut.settext("Next", 20, Color::Black);
	nextbut.loadfont(font);
	nextbut.sethovertexture(largehover, 0, 0);
	nextbut.hover(true);
	nextbut.magnify(true);

	playbut.settexture(largetexture, largenormal);
	playbut.setdim(dimensions);
	playbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	playbut.setorigin();

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
	settingbut.setdim(dimensions);
	settingbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	settingbut.setorigin();
	settingbut.alignv(playbutposition, largebuttonheight);
	settingbut.settext("Settings", 20, Color::Black);
	settingbut.loadfont(font);
	settingbut.sethovertexture(largehover, 0, 0);
	settingbut.hover(true);
	settingbut.magnify(true);

	storybut.settexture(largetexture, largenormal);
	storybut.setdim(dimensions);
	storybut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	storybut.setorigin();
	storybut.alignv((settingbut.returnpos()), largebuttonheight);
	storybut.settext("Story", 20, Color::Black);
	storybut.loadfont(font);
	storybut.sethovertexture(largehover, 0, 0);
	storybut.hover(true);
	storybut.magnify(true);

	highscorebut.settexture(largetexture, largenormal);
	highscorebut.setdim(dimensions);
	highscorebut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	highscorebut.setorigin();
	highscorebut.alignv(storybut.returnpos(), largebuttonheight);
	highscorebut.settext("Highscore", 20, Color::Black);
	highscorebut.loadfont(font);
	highscorebut.sethovertexture(largehover, 0, 0);
	highscorebut.hover(true);
	highscorebut.magnify(true);

	creditsbut.settexture(largetexture, largenormal);
	creditsbut.setdim(dimensions);
	creditsbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	creditsbut.setorigin();
	creditsbut.alignv(highscorebut.returnpos(), largebuttonheight);
	creditsbut.settext("Credits", 20, Color::Black);
	creditsbut.loadfont(font);
	creditsbut.sethovertexture(largehover, 0, 0);
	creditsbut.hover(true);
	creditsbut.magnify(true);

	quitbut.settexture(largetexture, largenormal);
	quitbut.setdim(dimensions);
	quitbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	quitbut.setorigin();
	quitbut.alignv(creditsbut.returnpos(), largebuttonheight);
	quitbut.settext("Quit", 20, Color::Black);
	quitbut.loadfont(font);
	quitbut.sethovertexture(largehover, 0, 0);
	quitbut.hover(true);
	quitbut.magnify(true);

	backbut.setdim(dimensions);
	backbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	backbut.settexture(largetexture, largenormal);
	backbut.setorigin();
	backbut.centerh(*gameheight / 1.010);
	backbut.loadfont(font);
	backbut.settext("Back", 25, Color::Black);
	backbut.sethovertexture(largehover, 0, 0);
	backbut.magnify(true);
	backbut.hover(true);

	easy.setdim(dimensions);
	easy.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	easy.settexture(smalltexture, smallnormal);
	easy.settexture(smallpressed);
	easy.setorigin();

	easyposition = new Vector2f;
	easyposition->x = *gamewidth / 2.5;
	easyposition->y = *gameheight / 3.5;

	easy.setposition(easyposition);
	easy.loadfont(font);
	easy.settext("E", 25, Color::Black);
	easy.hover(true);
	easy.sethovertexture(smallhover, 0, 0);
	easy.magnify(true);

	medium.setdim(dimensions);
	medium.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	medium.settexture(smalltexture, smallnormal);
	medium.setorigin();
	medium.alignh(easy.returnpos(), 1.5*smallbuttonwidth);
	medium.loadfont(font);
	medium.settext("M", 25, Color::Black);
	medium.hover(true);
	medium.sethovertexture(smallhover, 0, 0);
	medium.magnify(true);

	hard.setdim(dimensions);
	hard.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	hard.settexture(smalltexture, smallnormal);
	hard.setorigin();
	hard.alignh(medium.returnpos(), 1.5*smallbuttonwidth);
	hard.loadfont(font);
	hard.settext("H", 25, Color::Black);
	hard.hover(true);
	hard.sethovertexture(smallhover, 0, 0);
	hard.magnify(true);

	onbutposition = new Vector2f;
	onbutposition->x = *gamewidth / 2.5;
	onbutposition->y = *gameheight / 2.1;

	on.setdim(dimensions);
	on.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	on.settexture(smalltexture, smallnormal);
	on.settexture(smallpressed);
	on.setorigin();
	on.setposition(onbutposition);
	on.loadfont(font);
	on.settext("On", 19, Color::Black);
	on.hover(true);
	on.sethovertexture(smallhover, 0, 0);
	on.magnify(true);

	off.setdim(dimensions);
	off.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	off.settexture(smalltexture, smallnormal);
	off.setorigin();
	off.alignh(on.returnpos(), 1.5*smallbuttonwidth);
	off.loadfont(font);
	off.settext("Off", 19, Color::Black);
	off.hover(true);
	off.sethovertexture(smallhover, 0, 0);
	off.magnify(true);

	singlebutpos = new Vector2f;
	singlebutpos->x = *gamewidth / 2;
	singlebutpos->y = *gameheight / 3;

	singlebut.setposition(singlebutpos);
	singlebut.settexture(largetexture, largenormal);
	singlebut.setdim(dimensions);
	singlebut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	singlebut.setorigin();
	singlebut.settext("Single Player", 17, Color::Black);
	singlebut.loadfont(font);
	singlebut.sethovertexture(largehover, 0, 0);
	singlebut.hover(true);
	singlebut.magnify(true);

	multiplayerbut.settexture(largetexture, largenormal);
	multiplayerbut.setdim(dimensions);
	multiplayerbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	multiplayerbut.setorigin();
	multiplayerbut.alignv(singlebut.returnpos(), 2.5 * largebuttonheight);
	multiplayerbut.settext("Multiplayer", 20, Color::Black);
	multiplayerbut.loadfont(font);
	multiplayerbut.sethovertexture(largehover, 0, 0);
	multiplayerbut.hover(true);
	multiplayerbut.magnify(true);

	newbutposition = new Vector2f;
	newbutposition->x = *gamewidth / 2;
	newbutposition->y = *gameheight / 2.5;

	gamebuttonpos = new Vector2f;
	gamebuttonpos->x = *gamewidth / 2;
	gamebuttonpos->y = *gameheight * 3 / 4;

	buttonpointer = new button;
	buttonpointer->setcolor(Color::Transparent);
	buttonpointer->setdim(dimensions);

	for (int i = 0; i < 5; i++)
		buttonvectotr.push_back(*buttonpointer);


	buttonvectotr[0].setposition(&sf::Vector2f(*gamewidth / 3, *gameheight*0.6));
	buttonvectotr[1].setposition(&(*buttonvectotr[0].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[2].setposition(&(*buttonvectotr[1].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[3].setposition(&(*buttonvectotr[2].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[4].setposition(&(*buttonvectotr[3].returnpos() + sf::Vector2f(4 * image.x, 0)));

	buttonvectotr[0].hover(true);
	buttonvectotr[1].hover(true);
	buttonvectotr[2].hover(true);
	buttonvectotr[3].hover(true);
	buttonvectotr[4].hover(true);

	buttonvectotr[0].setsize(Vector2f(21, 19));
	buttonvectotr[1].setsize(Vector2f(21, 19));
	buttonvectotr[2].setsize(Vector2f(21, 19));
	buttonvectotr[3].setsize(Vector2f(21, 19));
	buttonvectotr[4].setsize(Vector2f(21, 19));
	Player *frogtemp;

	frogtemp = new Player;

	Vector2f *gamedi;
	gamedi = new Vector2f;
	gamedi->x = *gamewidth;
	gamedi->y = *gameheight;

	frogtemp->gamedimension(gamedi);
	frogtemp->settexture(frogtexture[0]);
	frogtemp->setintrect(IntRect(229, 235, 23, 20));

	Vector2f* frogposition;
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
	frogtemp->speed(0);

	for (int i = 0; i < 5; i++)
		frogtempvec.push_back(*frogtemp);

	frogtempvec[0].settexture(frogtexture[0]);
	frogtempvec[1].settexture(frogtexture[1]);
	frogtempvec[2].settexture(frogtexture[2]);
	frogtempvec[3].settexture(frogtexture[3]);
	frogtempvec[4].settexture(frogtexture[4]);

	frogtempvec[0].setpos(buttonvectotr[0].returnpos());
	frogtempvec[1].setpos(buttonvectotr[1].returnpos());
	frogtempvec[2].setpos(buttonvectotr[2].returnpos());
	frogtempvec[3].setpos(buttonvectotr[3].returnpos());
	frogtempvec[4].setpos(buttonvectotr[4].returnpos());
}
void renderer(RenderWindow& window)
{
	window.clear(Color::Green);
	if (homeflag &&!settingflag &&!storyflag &&!highscoreflag &&!creditflag&&!singlemultiflag)
	{
		home.render(window);
void setscale(RenderWindow &);


		playbut.render(window);
		settingbut.render(window);
		storybut.render(window);
		highscorebut.render(window);
		quitbut.render(window);
		creditsbut.render(window);
	}
	if (settingflag)
	{
		settingm.render(window);
		backbut.render(window);
		easy.render(window);
		medium.render(window);
		hard.render(window);
		on.render(window);
		off.render(window);
	}
	if (storyflag)
	{
		storymenu.render(window);
		backbut.render(window);
	}
	if (creditflag)
	{
		creditm.render(window);
		backbut.render(window);
	}
	if (singlemultiflag)
	{
		/*singmulti.render(window);
		backbut.render(window);
		singlebut.render(window);
		multiplayerbut.render(window);*/

		if (frog.size()>1)
			window.setView(view2);

		//game.render(window);
		one.render(window);

		for (int i = 0; i < enemy.size(); i++)
		for (int j = 0; j < enemy[i].size(); j++)
			enemy[i][j].render(window);

		for (int i = 0; i < helper.size(); i++)
		for (int j = 0; j < helper[i].size(); j++)
			helper[i][j].render(window);

		frog[0].render(window);
		if (frog.size()>1)
			frog[1].render(window);

		if (frog.size()>1)
		{
			window.setView(view1);
			//game.render(window);

			one.render(window);

			for (int i = 0; i < enemy.size(); i++)
			for (int j = 0; j < enemy[i].size(); j++)
				enemy[i][j].render(window);

			for (int i = 0; i < helper.size(); i++)
			for (int j = 0; j < helper[i].size(); j++)
				helper[i][j].render(window);

			frog[1].render(window);
			frog[0].render(window);
		}

	}

	if (nameflag)
	{
		namem.render(window);
		window.draw(inputname);
		backbut.render(window);

		for (int i = 0; i < 5; i++)
		{
			buttonvectotr[i].render(window);
			frogtempvec[i].render(window);
		}

		nextbut.render(window);
	}
	window.display();
}
void setscale(RenderWindow & window)
{

	*gamewidth = window.getSize().x;
	*gameheight = window.getSize().y;
	dimensions = &Vector2f(*gamewidth, *gameheight);

	inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));

	home.setscale(dimensions);
	settingm.setscale(dimensions);
	storymenu.setscale(dimensions);
	creditm.setscale(dimensions);
	singmulti.setscale(dimensions);
	namem.setscale(dimensions);

	//inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));

	playbutposition->x = *gamewidth / 9.5 + largebuttonwidth / 2;
	playbutposition->y = *gameheight / 4.65 + largebuttonheight / 2;

	easyposition->x = *gamewidth / 2.5;
	easyposition->y = *gameheight / 3.5;


	onbutposition->x = *gamewidth / 2.5;
	onbutposition->y = *gameheight / 2.1;

	singlebutpos->x = *gamewidth / 2;
	singlebutpos->y = *gameheight / 3;

	newbutposition->x = *gamewidth / 2;
	newbutposition->y = *gameheight / 2.5;


	playbut.setscale(dimensions);
	settingbut.setscale(dimensions);
	storybut.setscale(dimensions);
	highscorebut.setscale(dimensions);
	creditsbut.setscale(dimensions);
	quitbut.setscale(dimensions);
	singlebut.setscale(dimensions);

	multiplayerbut.setscale(dimensions);

	backbut.centerh(*gameheight / 1.010);

	backbut.setscale(dimensions);
	easy.setscale(dimensions);
	medium.setscale(dimensions);
	hard.setscale(dimensions);
	on.setscale(dimensions);
	off.setscale(dimensions);

	nextbutposition->x = *gamewidth / 1.75;
	nextbutposition->y = *gameheight / 1.5;
	nextbut.setscale(dimensions);

	gamebuttonpos->x = *gamewidth / 2.5;
	gamebuttonpos->y = *gameheight / 1.5;

	for (int i = 0; i < buttonvectotr.size(); i++)
	{
		buttonvectotr[i].setscale(dimensions);
	}
}


void handlelevels(Clock& clock)
{
	///////////////////////
	///////////////////////
	//if (clock.getelapsedtime().asSeconds() > 20)
	//lives--;
	///////////////////////////
	//clock for both
	///////////////////////
	if (!keypressed && clock.getElapsedTime().asSeconds() > 20)
		lives--;

	if (!keypressed2 && clock.getElapsedTime().asSeconds() > 20)
		lives2--;

	///////////////////////
	//////////////////////
	Obstacle obstacle;

	for (int i = 0; i < enemy.size(); i++)
	for (int j = 0; j < enemy[i].size(); j++)
	for (int k = 0; k < frog.size(); k++)
	{
		if (obstacle.ifmet(frog[k], enemy[i][j]))
		{
			frog[k].setintrect(IntRect(229, 235, 23, 20));

			frog[k].setpos(&Vector2f(*gamewidth / 2, *gameheight*.95));

			//obstacle.playermovewithhelper(frog, car);
		}
	}

	//need to add boundary of water// needs to be vector-changes betwwen levels// + time
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//

	for (int i = 0; i < helper.size(); i++)
	for (int j = 0; j < helper[i].size(); j++)
	for (int k = 0; k < frog.size(); k++)
	{
		if (obstacle.ifmet(frog[k], helper[i][j]) && !obstacle.boundary(frog[k], *gamewidth - speed[0][k], 0, *gamewidth, *gameheight)
			&& !obstacle.boundary(frog[k], 0, 0, speed[0][k], *gameheight))
		{
			obstacle.playermovewithhelper(frog[k], helper[i][j]);
		}
	}


	if (clock.getElapsedTime().asSeconds() > .1)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			for (int j = 0; j < enemy[i].size(); j++)
				enemy[i][j].speed(scalefactor->x*clock.getElapsedTime().asSeconds() * speed[1][i*enemy[i].size() + j] * enemyspeedfactor);
		}

		for (int i = 0; i < helper.size(); i++)
		{
			for (int j = 0; j < helper[i].size(); j++)
				helper[i][j].speed(scalefactor->x*clock.getElapsedTime().asSeconds() * speed[2][i*helper[i].size() + j] * helperspeedfactor);
		}

		/*for (int i = 0; i < frog.size(); i++)
		{
		frog[i].speed(10*clock.getElapsedTime().asSeconds() * speed[0][i]*playerspeedfactor);
		}
		*/

		clock.restart();

		//for (int i = 0; i < frog.size(); i++)
		if (animationcounter < 3 && keypressed)
		{
			frog[0].update(3);
			animationcounter++;
		}
		else
		{
			animationcounter = 0;
			if (keypressed)
				keypressed = false;
		}

		if (keypressed2&& animationcounter2<3 && frog.size()>1)
		{
			frog[1].update(3);
			animationcounter2++;
		}
		else
		{
			animationcounter2 = 0;
			if (keypressed2)
				keypressed2 = false;
		}

		bool water = false;

		for (int i = 0; i < frog.size(); i++)
		for (int j = 0; j < waterpos.size(); j++)
		{
			if (obstacle.boundary(frog[i], waterpos[j].left, waterpos[j].top, waterpos[j].width, waterpos[j].height)
				&& animationcounter == 0)
			{
				for (int k = 0; k < helper.size(); k++)
				for (int l = 0; l < helper[k].size(); l++)
				if (obstacle.ifmet(frog[i], helper[k][l]))
				{
					water = true;
				}
			}
			if (obstacle.boundary(frog[i], waterpos[j].left, waterpos[j].top, waterpos[j].width, waterpos[j].height)
				&& animationcounter == 0)
			if (!water)
			{
				frog[i].setintrect(IntRect(229, 235, 23, 20));

				frog[i].setpos(&Vector2f(*gamewidth / 2, *gameheight*.95));
			}

			water = false;

		}


		if (!keypressed)
		{
			if (!obstacle.boundary(frog[0], *gamewidth - speed[0][0] * 4, 0, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveright();
				keypressed = true;

			}

			if (!obstacle.boundary(frog[0], 0, 0, 3 * speed[0][0], *gameheight/**scalefactor->y*/))
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveleft();
				keypressed = true;

			}

			if (!obstacle.boundary(frog[0], 0, 0, *gamewidth/**scalefactor->y*/, 3 * speed[0][0]))
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveup();
				keypressed = true;
			}

			if (!obstacle.boundary(frog[0], 0, *gameheight - 3 * speed[0][0]/**scalefactor->y*/, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				frog[0].speed(speed[0][0]);
				frog[0].movedown();
				keypressed = true;
			}
		}
		if (frog.size() > 1 && !keypressed2)
		{

			if (!obstacle.boundary(frog[1], *gamewidth - speed[0][1] * 4, 0, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				frog[1].speed(speed[0][1]);
				frog[1].moveright();
				keypressed2 = true;

			}

			if (!obstacle.boundary(frog[1], 0, 0, 3 * speed[0][1], *gameheight/**scalefactor->y*/))
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				frog[1].speed(speed[0][1]);
				frog[1].moveleft();
				keypressed2 = true;

			}
			if (!obstacle.boundary(frog[1], 0, 0, *gamewidth/**scalefactor->y*/, 3 * speed[0][1]))
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				frog[1].speed(speed[0][1]);
				frog[1].moveup();
				keypressed2 = true;
			}


			if (!obstacle.boundary(frog[1], 0, *gameheight - 3 * speed[0][1]/**scalefactor->y*/, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				frog[1].speed(speed[0][1]);
				frog[1].movedown();
				keypressed2 = true;
			}

		}
	}






	for (int i = 0; i < direction.size(); i++)
	for (int j = 0; j < direction[i].size(); j++)
	{
		for (int k = 0; k < direction[i][j].size(); k++)
		{
			if (j == 0)
			{
				if (i == 0)
					enemy[direction[i][j][k].i][direction[i][j][k].j].moveright();
				else
					helper[direction[i][j][k].i][direction[i][j][k].j].moveright();
			}
			if (j == 1)
			{
				if (i == 0)
					enemy[direction[i][j][k].i][direction[i][j][k].j].moveleft();
				else
					helper[direction[i][j][k].i][direction[i][j][k].j].moveleft();
			}
			if (j == 2)
			{
				if (i == 0)
					enemy[direction[i][j][k].i][direction[i][j][k].j].moveup();
				else
					helper[direction[i][j][k].i][direction[i][j][k].j].moveup();

			}
			if (j == 3)
			{
				if (i == 0)
					enemy[direction[i][j][k].i][direction[i][j][k].j].movedown();
				else
					helper[direction[i][j][k].i][direction[i][j][k].j].movedown();
			}

		}



	}

}

void setlevel1()
{

	int enemycol = 9;
	int enemyrow = 1;

/*
	Vector2f *gamedim;
	gamedim = new Vector2f;
	gamedim->x = gamewidth;
	gamedim->y = gameheight;
*/
	vector<Enemy> enem;
	Enemy *enemytemp;

	enemytemp = new Enemy;

	vector<float> speedtemp(enemycol, .75);

	enemytemp->settexture(*carpicpointer);
	//car.setintrect(IntRect(5, 148, 56, 34));
	enemytemp->numofrtsprite(1);
	enemytemp->setrightrect(1, IntRect(5, 148, 56, 34));

	enemytemp->numofltsprite(1);
	enemytemp->setleftrect(1, IntRect(5, 148, 56, 34));

	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();

	for (int i = 0; i < enemycol; i++)
	{
		enem.push_back(*enemytemp);
	}

	enemyposition = new Vector2f;


	((enemyposition))->x = *gamewidth/2;
	((enemyposition))->y = *gameheight*.85;

	enem[0].setpos(enemyposition, &Vector2f(0, 0));

	enemychange = new Vector2f*[enemycol - 1];

	for (int i = 0; i < enemycol - 1; i++)
		enemychange[i] = new Vector2f;

	enemychange[0]->x = 0 - ((enemyposition))->x;
	enemychange[0]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[1]->x = *gamewidth  / 4 - ((enemyposition))->x;
	enemychange[1]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[2]->x = *gamewidth*3/4 - ((enemyposition))->x;
	enemychange[2]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[3]->x = 0 - ((enemyposition))->x;
	enemychange[3]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[4]->x = *gamewidth / 3 - ((enemyposition))->x;
	enemychange[4]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[5]->x = *gamewidth*2/3 - ((enemyposition))->x;
	enemychange[5]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[6]->x = *gamewidth / 4 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.65 - ((enemyposition))->y;

	enemychange[6]->x = *gamewidth * 3 / 4 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.65 - ((enemyposition))->y;

	enemychange[7]->x = *gamewidth / 2 - ((enemyposition))->x;
	enemychange[7]->y = *gameheight*.55 - ((enemyposition))->y;


	for (int i = 1; i < enem.size(); i++)
	{
		enem[i].setpos(enemyposition, enemychange[i - 1]);
	}




	speedtemp[4] = 1;


	speedtemp[5] = 1;


	speedtemp[6] = 1;


	speedtemp[7] = 1.5;


	speedtemp[8] = 1.5;

	enemy.push_back(enem);
	speed.push_back(speedtemp);
	
	int helpercol = 6;
	int helperrow = 1;

	vector<Helper> help;
	Helper *helptemp;


	helptemp = new Helper;

	
	(helptemp)->settexture(*carpicpointer);
	(helptemp)->setintrect(IntRect(5, 148, 56, 34));
	(helptemp)->numofrtsprite(1);
	(helptemp)->setrightrect(1, IntRect(5, 148, 56, 34));
	(helptemp)->numofltsprite(1);
	(helptemp)->setleftrect(1, IntRect(5, 148, 56, 34));
	(helptemp)->repeated(true);
	(helptemp)->gamedimension(gamedim);
	(helptemp)->setrandom();
	

	for (int j = 0; j < helpercol; j++)
	{
		help.push_back(*helptemp);
	}

	speedtemp.resize(helpercol);


	helperposition = new Vector2f;
	((helperposition))->x = *gamewidth / 4;
	((helperposition))->y = *gameheight*.15;

	help[0].setpos(helperposition, &Vector2f(0,0));

	helperchange = new Vector2f*[helpercol-1];

	for (int i = 0; i < helpercol - 1; i++)
		helperchange[i] = new Vector2f;

	helperchange[0]->x = 0 - (helperposition)->x;
	helperchange[0]->y = gamedim[1][0]*.25 - gamedim[1][0]*.15;

	helperchange[1]->x = gamedim[0][0] * 3 / 4 - (helperposition)->x;
	helperchange[1]->y = gamedim[1][0]*.25 - gamedim[1][0]*.15;

	helperchange[2]->x = 0 - (helperposition)->x;
	helperchange[2]->y = gamedim[1][0] * .35 - gamedim[1][0]*.15;

	helperchange[3]->x = gamedim[0][0] / 3 - (helperposition)->x;
	helperchange[3]->y = gamedim[1][0]*.35 - gamedim[1][0]*.15;

	helperchange[4]->x = gamedim[0][0] * 2 / 3 - (helperposition)->x;
	helperchange[4]->y = gamedim[1][0]*.35 - gamedim[1][1]*.15;


	for (int i = 1; i < help.size(); i++)
	{
		help[i].setpos(helperposition, helperchange[i - 1]);
	}



	/*vector<Vector2f*> helperpos;
	Vector2f *position;

	position = new Vector2f;
	((position))->x = gamewidth /2;
	((position))->y = gameheight*.15;
	
	helperpos.push_back(position);
	position = new Vector2f;
	((position))->x = gamewidth *2/3;
	((position))->y = gameheight*.25;

	helperpos.push_back(position);
	position = new Vector2f;
	((position))->x = gamewidth/3;
	((position))->y = gameheight*.25;

	helperpos.push_back(position);
	position = new Vector2f;
	((position))->x = gamewidth  / 4;
	((position))->y = gameheight*.35;

	helperpos.push_back(position);
	position = new Vector2f;
	((position))->x = gamewidth  / 2;
	((position))->y = gameheight*.35;

	helperpos.push_back(position);

	position = new Vector2f;
	((position))->x = gamewidth *3/4;
	((position))->y = gameheight*.35;

	helperpos.push_back(position);

	helperposition.push_back(helperpos);*/


	//help[0].setpos(helperpos[0]);
	speedtemp[0] = 2;

	//help[1].setpos(helperpos[1]);
	speedtemp[1] = 2;


	//help[2].setpos(helperpos[2]);
	speedtemp[2] = 2;

	//help[3].setpos(helperpos[3]);
	speedtemp[3] = 1;

	//help[4].setpos(helperpos[4]);
	speedtemp[4] = 1;

	//help[5].setpos(helperpos[5]);
	speedtemp[5] = 1;

	helper.push_back(help);
	speed.push_back(speedtemp);

	vector<vector<arraypos>> temp;
	vector <arraypos> tempdirec;

	tempdirec.push_back(arraypos(0, 0));
	tempdirec.push_back(arraypos(0, 1));
	tempdirec.push_back(arraypos(0, 2));
	tempdirec.push_back(arraypos(0, 3));
	tempdirec.push_back(arraypos(0, 7));
	tempdirec.push_back(arraypos(0, 8));

	temp.push_back(tempdirec);

	tempdirec.clear();
	tempdirec.push_back(arraypos(0, 4));
	tempdirec.push_back(arraypos(0, 5));
	tempdirec.push_back(arraypos(0, 6));

	temp.push_back(tempdirec);

	direction.push_back(temp);

	temp.clear();
	tempdirec.clear();
	
	tempdirec.push_back(arraypos(0, 0));
	tempdirec.push_back(arraypos(0, 3));
	tempdirec.push_back(arraypos(0, 4));
	tempdirec.push_back(arraypos(0, 5));

	temp.push_back(tempdirec);
	tempdirec.clear();

	tempdirec.push_back(arraypos(0, 1));
	tempdirec.push_back(arraypos(0, 2));

	temp.push_back(tempdirec);

	direction.push_back(temp);

	temp.clear();
	tempdirec.clear();

	waterpos.push_back(IntRect(0, *gameheight/10, *gamewidth, *gameheight*.4));
}
void setlevel1resolution(RenderWindow& window, Level& one)
{
	*gamewidth = window.getSize().x;
	*gameheight = window.getSize().y;

	frogposition->x = *gamewidth / 2;
	frogposition->y = *gameheight *.95;

	/**gamedim = *gamewidth;
	*(gamedim+1)=*gameheight);
	*/
	Vector2f *gamescaledim;

	gamescaledim = new Vector2f;
	
	gamescaledim->x=(*gamewidth);
	gamescaledim->y=(*gameheight);


	//fullscreen = false;
	one.levelscale(gamescaledim);
	frog[0].scale(gamescaledim);

	if (frog.size() > 1)
	{
		frog[1].scale(gamescaledim);
		speed[0][1] = (*gameheight *.10) / 3;

	}
	speed[0][0] = (*gameheight *.10) / 3;

	//Vector2f *position3;

	// = new Vector2f;

	(helperposition)->x = *gamewidth / 4;
	(helperposition)->y = *gameheight*.15;

	Vector2f* helperscale;
	helperscale = new Vector2f;
	helperscale->x = gamedim[0][0] / oldgamedim->x;
	helperscale->y = gamedim[1][0] / oldgamedim->y;

	helper[0][0].setpos(helperposition, &Vector2f(0, 0));
	for (int i = 1; i < helper[0].size(); i++)
	{
		helper[0][i].setpos(helperposition, helperchange[i - 1]);
	}

	helperchange[0]->x = 0 - (helperposition)->x;
	helperchange[0]->y = gamedim[1][0] * .25 - gamedim[1][0] * .15;

	helperchange[1]->x = gamedim[0][0] * 3 / 4 - (helperposition)->x;
	helperchange[1]->y = gamedim[1][0] * .25 - gamedim[1][0] * .15;

	helperchange[2]->x = 0 - (helperposition)->x;
	helperchange[2]->y = gamedim[1][0] * .35 - gamedim[1][0] * .15;

	helperchange[3]->x = gamedim[0][0] / 3 - (helperposition)->x;
	helperchange[3]->y = gamedim[1][0] * .35 - gamedim[1][0] * .15;

	helperchange[4]->x = gamedim[0][0] * 2 / 3 - (helperposition)->x;
	helperchange[4]->y = gamedim[1][0] * .35 - gamedim[1][1] * .15;

	for (int i = 0; i < helper.size(); i++)
	for (int j = 1; j < helper[i].size(); j++)
		helper[i][j].scale(helperscale);

	helper[0][0].scale(helperscale);

	(enemyposition)->x = *gamewidth / 2;
	(enemyposition)->y = *gameheight*.85;

	enemy[0][0].setpos(enemyposition, &Vector2f(0, 0));

	enemychange[0]->x = 0 - ((enemyposition))->x;
	enemychange[0]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[1]->x = *gamewidth / 4 - ((enemyposition))->x;
	enemychange[1]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[2]->x = *gamewidth * 3 / 4 - ((enemyposition))->x;
	enemychange[2]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[3]->x = 0 - ((enemyposition))->x;
	enemychange[3]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[4]->x = *gamewidth / 3 - ((enemyposition))->x;
	enemychange[4]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[5]->x = *gamewidth * 2 / 3 - ((enemyposition))->x;
	enemychange[5]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[6]->x = *gamewidth / 4 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.65 - ((enemyposition))->y;

	enemychange[6]->x = *gamewidth * 3 / 4 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.65 - ((enemyposition))->y;

	enemychange[7]->x = *gamewidth / 2 - ((enemyposition))->x;
	enemychange[7]->y = *gameheight*.55 - ((enemyposition))->y;


	Vector2f *enemyscale;
	enemyscale = new Vector2f;
	enemyscale->x = gamedim[0][0] / oldgamedim->x;
	enemyscale->y = gamedim[1][0] / oldgamedim->y;

	for (int i = 1; i < enemy[0].size(); i++)
	{
		enemy[0][i].setpos(enemyposition, enemychange[i - 1]);
	}


	/*for (int i = 0; i < enemy.size(); i++)
	for (int j = 1; j < enemy[i].size(); j++)
		enemy[i][j].gamedimension(gamedim);

	for (int i = 0; i < helper.size(); i++)
	for (int j = 1; j <helper[i].size(); j++)
		helper[i][j].gamedimension(gamedim);*/

	for (int i = 0; i < enemy.size(); i++)
	for (int j = 1; j < enemy[i].size(); j++)
		enemy[i][j].scale(enemyscale);

	

	enemy[0][0].scale(enemyscale);

	Vector2f *gamed;

	gamed = new Vector2f;

	gamed->x = gamedim[0][0];
	gamed->y = gamedim[1][0];

	one.levelscale(gamed);

	scalefactor->x = gamedim[0][0] / oldgamedim->x;
	scalefactor->y = gamedim[1][0] / oldgamedim->y;

	for (int i = 0; i < waterpos.size(); i++)
	{
		waterpos[i].width *= scalefactor->x;
		waterpos[i].height *= scalefactor->y;
	}

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;


	if (frog.size()>1)
	{
		view1.setSize(*gamewidth / 2, *gameheight);
		view2.setSize(*gamewidth / 2, *gameheight);
		view1.setCenter(*gamewidth / 2, *gameheight / 2);
		view2.setCenter(*gamewidth / 2, *gameheight / 2);
	}

}