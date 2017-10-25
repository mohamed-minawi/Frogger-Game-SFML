#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
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
#include "Splashscreen.h"


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

SoundBuffer *soundloader[2];

Texture *hometexture, *largetexture, *background, *smalltexture, *gametile;

Font font, titlefont;

bool homeflag = true, settingflag = false, storyflag = false, creditflag = false, highscoreflag = false, nameflag = false, singlemultiflag = false, charchosen = false, namechosen = false, m = false, nextflag = false, s = false, gameflag = false, e=true, med=false, had = false;;
bool win = false, lose = false;

button playbut, settingbut, quitbut, highscorebut, creditsbut, storybut, backbut, easy, medium, hard, on, off, singlebut, multiplayerbut, nextbut;
menu home, settingm, storymenu, creditm, charm, namem, singmulti, singlem, multim;
Text inputname;
string str;
int counter;
Texture *frogtexture[5];
vector<Player> frogtempvec;
bool soundplay = true;
vector<button> buttonvectotr;
vector<Player> avatartempvec;
vector<IntRect> charint;
IntRect oldrect(229, 235, 23, 20);
IntRect newrect(200, 138, 23, 20);
IntRect mid;
button*  buttonpointer;
Texture *avatartexture[3];

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
Vector2f *frogbutton;
bool animation = false;

Vector2f *oldgamedim;
Player *avatartemp, *avatar2temp, *avatar3temp;
Texture *temp;
Sprite temp1;

#define buttonwidth 105
#define buttonheight 40
Texture *carpicpointer;
bool keypressed = false, keypressed2 = false;
int animationcounter = 0, animationcounter2 = 0, levelcount = 1;
float enemyspeedfactor = 1, helperspeedfactor = 1, playerspeedfactor = 1;
int lives = 7, lives2 = 7;
Vector2f* helperposition, **helperchange, *enemyposition, **enemychange;
Vector2f *scalefactor;
float **gamedim;
View view1, view2;
Level *one;
int maxlevel=1;
int highscore = 0;
Text nameoutput;
Text liveoutput;
Text timeleft;
Text highscoreoutput;
Clock clock2;
SplashScreen *storyscreen, *loadscreen;
bool loadflag = true;
Texture *winscreen, *losescreen;
Texture *logoscreen;
Sprite winsprite, losesprite, logosprite;

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
vector<IntRect> winpos;
//vector<vector<Vector2f*>> helperposition;

Vector2f *frogposition;

IntRect loadintrect[13];
IntRect loadintrectstory[7];
void loadstoryint();
void loadscreenint();

void handlelevels(Clock&);

void setlevel1();
void setlevel1resolution(RenderWindow&, Level&);
void setscale(RenderWindow&);
void loader();
void renderer(RenderWindow&);

void main()
{
	SoundBuffer begin, game;
	Sound intro, plays;
	soundloader[0] = &begin;
	soundloader[1] = &game;
	intro.setBuffer(begin);
	plays.setBuffer(game);

	Texture hometextur, largetextur, backgroun, smalltextur, gametil;

	hometexture = &hometextur;
	largetexture = &largetextur;
	background = &backgroun;
	smalltexture = &smalltextur;
	gametile = &gametil;

	Texture frogtextur[5];

	frogtexture[0] = &frogtextur[0];
	frogtexture[1] = &frogtextur[1];
	frogtexture[2] = &frogtextur[2];
	frogtexture[3] = &frogtextur[3];
	frogtexture[4] = &frogtextur[4];

	Texture avatartextur[3];

	avatartexture[0] = &avatartextur[0];
	avatartexture[1] = &avatartextur[1];
	avatartexture[2] = &avatartextur[2];

	Texture temptt;
	temp = &temptt;

	Level levone("level1.txt");

	one = &levone;

	int animationcounter = 0, countswitch = 0;
	Clock clock;
	gamewidth = new float;
	*gamewidth = 1360;

	gameheight = new float;
	*gameheight = 700;

	dimensions = &Vector2f(*gamewidth, *gameheight);

	RenderWindow window(VideoMode(*gamewidth, *gameheight, 32), "Frogger Game, Abdelrahman Youssef, Mohammed Minawi, Mohammed Yasser", Style::Fullscreen);


	Texture hometexture, buttexture, gametext;

	frog.reserve(2);
	scalefactor = new Vector2f;
	scalefactor->x = 1;
	scalefactor->y = 1;

	gamedim = new float*[2];


	*gamedim = gamewidth;
	*(gamedim + 1) = gameheight;


	SplashScreen story;

	loadstoryint();


	Texture storyimg, logo;

	storyimg.loadFromFile("Story.png");

	winscreen = &storyimg;

	storyimg.setSmooth(true);
	storyimg.setRepeated(true);

	logo.loadFromFile("Drawing.png");

	story.numofpic(7);
	story.settexture(storyimg);
	for (int i = 0; i < 7; i++)
	{
		story.loadcontent(i + 1, loadintrectstory[i]);
	}
	Vector2u j(loadintrectstory[0].width, loadintrectstory[0].height);
	story.screensize(*gamewidth, *gameheight);
	story.size(j);
	story.setlogo(logo);

	storyscreen = &story;

	logoscreen = &logo;

	SplashScreen load;

	loadscreenint();
	Texture loadimg;

	loadimg.loadFromFile("Kermit.png");

	loadimg.setSmooth(true);
	loadimg.setRepeated(true);

	logo.loadFromFile("Drawing.png");

	load.numofpic(13);
	load.settexture(loadimg);
	for (int i = 0; i < 13; i++)
	{
		load.loadcontent(i + 1, loadintrect[i]);
	}
	Vector2u k(loadintrect[0].width, loadintrect[0].height);
	load.screensize(*gamewidth, *gameheight);
	load.size(k);
	load.setlogo(logo);

	losescreen = gametile;

	loadscreen = &load;

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



	oldgamedim = new Vector2f;

	setlevel1();

	float **fulldim;

	fulldim = new float*[2];

	fulldim[0] = new float;
	fulldim[1] = new float;
	fulldim[0][0] = window.getSize().x;
	fulldim[1][0] = window.getSize().y;

	Vector2f *fulld;

	fulld = new Vector2f;
	fulld->x = fulldim[0][0];
	fulld->y = fulldim[1][0];

	one->setgamedim(fulld);
	frog[0].gamedimension(fulld);
	//frog[1].gamedimension(fulld);

	view1.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	view2.setCenter(window.getSize().x / 2, window.getSize().y / 2);

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;



	setlevel1resolution(window, *one);

	//window.create(VideoMode(800, 500), "Mitcho Buttons");



	Vector2f positionofchar;

	loader();

	Vector2i mp;
	if (soundplay)
		intro.play();

	if (gameflag) {
		intro.stop();
		plays.play();

	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			
			mp = Mouse::getPosition(window);
			if (event.type == sf::Event::Closed || event.key.code == Keyboard::Escape)
				window.close();
			if (gameflag)
			if (event.key.code == Keyboard::B)
			{
				gameflag = false;
				nameflag = false;
				homeflag = true;
				singlemultiflag = false;
				inputname.setString("");
				inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
				for (int i = 0; i < 5; i++)
				{
					charint[i] = oldrect;
				}
				str = "";
				if (e) lives = 5;
				if (med)  lives = 7;
				if (had)		lives = 9;
				win = false;
				lose = false;
				
				for (int i = 0; i < frog.size(); i++)
				{
					frog[i].setintrect(IntRect(229, 235, 23, 20));

					frog[i].setpos(&Vector2f(*gamewidth / 2, *gameheight*.95));
				}
				highscore = 0;
			}
			if (event.key.code == Keyboard::F11)
			{
				window.create(VideoMode(850, 650), "Mitcho Buttons");
				setscale(window);

				setlevel1resolution(window, *one);
				
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
					e = true;
				}
				else easy.returntooriginal();
				if (medium.ifhover(mp))
				{
					medium.hoverchange();
					med = true;
				}
				else medium.returntooriginal();
				if (hard.ifhover(mp))
				{
					hard.hoverchange();
					had = true;
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
					if (e) lives = 5;
					if (med)  lives = 7;
					if (had)		lives = 9;
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

				}

				if (s)
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
						nameoutput.setString("Name: " + str);
					}
					else if (event.text.unicode < 128 && event.text.unicode>65)
					{
						str += static_cast<char>(event.text.unicode);
						inputname.setString(str);
						nameoutput.setString("Name: " + str);
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

				if ((m&&charchosen&&namechosen) || s)
				{
					if (nextbut.ifhover(mp))
					{
						nextbut.hoverchange();

					}
					else nextbut.returntooriginal();
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
						helperspeedfactor = 1;
						enemyspeedfactor = 1;
						lives = 5;
					}

					if (medium.ifhover(ml))
					{
						easy.settexture(smallnormal);
						medium.settexture(smallpressed);
						hard.settexture(smallnormal);
						helperspeedfactor = 1.5;
						enemyspeedfactor = 1.5;
						lives = 7;
					}

					if (hard.ifhover(ml))
					{
						easy.settexture(smallnormal);
						medium.settexture(smallnormal);
						hard.settexture(smallpressed);
						enemyspeedfactor = 2;
						helperspeedfactor = 2;
						lives = 9;
					}
					if (on.ifhover(ml))
					{
						off.settexture(smallnormal);
						on.settexture(smallpressed);
						soundplay = true;
						intro.play();
					}
					if (off.ifhover(ml))
					{
						off.settexture(smallpressed);
						on.settexture(smallnormal);
						soundplay = false;
						intro.stop();
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
						s = true;
					}

					if (multiplayerbut.ifhover(ml))
					{
						
						homeflag = false;
						singlemultiflag = false;
						m = true;
						frog.push_back(frog[0]);
						speed[0].push_back(speed[0][0]);

						nameflag = true;
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
					if (counter == 0 && nextbut.ifhover(ml) && m &&charchosen && namechosen)
					{
						namem.setsubtitle(1, "Enter player two name", 22, Color::Red, Vector2f(2.1, 10));
						namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
						charchosen = false;
						namechosen = false;
						temp1.setPosition(positionofchar);


						counter = 1;
						str = "";
						inputname.setString("");
						inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
					}

					if (counter == 1 && nextbut.ifhover(ml) && m && charchosen && namechosen)
					{
						nameflag = false;
						gameflag = true;
						m = false;
						charchosen = false;
						namechosen = false;
						inputname.setString("");
						inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
					}
					if (s && charchosen &&namechosen && nextbut.ifhover(ml))
					{
						nameflag = false;
						gameflag = true;
						s = false;
						namechosen = false;
						charchosen = false;
						if (e) lives = 5;
						if (med)  lives = 7;
						if (had)		lives = 9;
					}
					if (backbut.ifhover(ml) && counter == 0 && m)
					{
						namem.setsubtitle(1, "Enter player one name", 22, Color::Red, Vector2f(2.1, 10));
						namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
						charchosen = false;
						namechosen = false;
						nameflag = false;
						singlemultiflag = true;
						m = false;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						counter = 0;
						str = "";

						inputname.setString("");
						inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
						temp1.setPosition(0, 0);
					}

					if (backbut.ifhover(ml) && counter == 1 && m)
					{
						namem.setsubtitle(1, "Enter player one name", 22, Color::Red, Vector2f(2.1, 10));
						namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
						charchosen = false;
						namechosen = false;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						counter = 0;
						str = "";
						inputname.setString("");
						inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
						temp1.setPosition(0, 0);
					}

					if (backbut.ifhover(ml) && s)
					{
						namem.setsubtitle(1, "Enter player one name", 22, Color::Red, Vector2f(2.1, 10));
						namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));
						charchosen = false;
						namechosen = false;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						str = "";
						nameflag = false;
						singlemultiflag = true;
						s = false;
						inputname.setString("");
						inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
					}

					if (buttonvectotr[0].ifhover(ml))
					{
						charchosen = true;

						if (frog.size() == 1)
						{
							frog[0].settexture(*frogtexture[0]);
						}
						else
						{
							frog[1].settexture(*frogtexture[0]);
						}

						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						charint[0] = newrect;
						mid = newrect;

						positionofchar = *buttonvectotr[0].returnpos();

					}
					if (buttonvectotr[1].ifhover(ml))
					{
						charchosen = true;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						charint[1] = newrect;
						mid = newrect;

						if (frog.size() == 1)
						{
							frog[0].settexture(*frogtexture[1]);
						}
						else
						{
							frog[1].settexture(*frogtexture[1]);
						}

						positionofchar = *buttonvectotr[1].returnpos();
					}
					if (buttonvectotr[2].ifhover(ml))
					{
						charchosen = true;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						charint[2] = newrect;
						mid = newrect;

						if (frog.size() == 1)
						{
							frog[0].settexture(*frogtexture[2]);
						}
						else
						{
							frog[1].settexture(*frogtexture[2]);
						}

						positionofchar = *buttonvectotr[2].returnpos();
					}
					if (buttonvectotr[3].ifhover(ml))
					{
						charchosen = true;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						charint[3] = newrect;
						mid = newrect;

						if (frog.size() == 1)
						{
							frog[0].settexture(*frogtexture[3]);
						}
						else
						{
							frog[1].settexture(*frogtexture[3]);
						}

						positionofchar = *buttonvectotr[3].returnpos();
					}
					if (buttonvectotr[4].ifhover(ml))
					{
						charchosen = true;
						for (int i = 0; i < 5; i++)
						{
							charint[i] = oldrect;
						}
						charint[4] = newrect;
						mid = newrect;

						if (frog.size() == 1)
						{
							frog[0].settexture(*frogtexture[4]);
						}
						else
						{
							frog[1].settexture(*frogtexture[4]);
						}

						positionofchar = *buttonvectotr[4].returnpos();
					}
				}
			}

		}

		if (nameflag)
		{
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
				else frogtempvec[0].setintrect(charint[0]);

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
				else frogtempvec[1].setintrect(charint[1]);

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
				else frogtempvec[2].setintrect(charint[2]);

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
				else frogtempvec[3].setintrect(charint[3]);

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
				else frogtempvec[4].setintrect(charint[4]);

			}
		}


		if (creditflag)
		{
			if (clock.getElapsedTime().asSeconds() > .1)
			{
				clock.restart();

				if (buttonvectotr[5].ifhover(mp))
				{
					if (animationcounter < 3 && animation)
					{
						avatartempvec[0].update(3);
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
							avatartempvec[0].speed(0);
							avatartempvec[0].moveright();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 1:
						{
							avatartempvec[0].speed(0);
							avatartempvec[0].moveleft();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 2:
						{
							avatartempvec[0].speed(0);
							avatartempvec[0].moveup();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 3:
						{
							avatartempvec[0].speed(0);
							avatartempvec[0].movedown();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						}



				}
				else avatartempvec[0].setintrect(IntRect(138, 10, 40, 52));
				if (buttonvectotr[6].ifhover(mp))
				{
					if (animationcounter < 3 && animation)
					{
						avatartempvec[1].update(3);
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
							avatartempvec[1].speed(0);
							avatartempvec[1].moveright();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 1:
						{
							avatartempvec[1].speed(0);
							avatartempvec[1].moveleft();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 2:
						{
							avatartempvec[1].speed(0);
							avatartempvec[1].moveup();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 3:
						{
							avatartempvec[1].speed(0);
							avatartempvec[1].movedown();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						}
				}
				else avatartempvec[1].setintrect(IntRect(138, 10, 40, 52));
				if (buttonvectotr[7].ifhover(mp))
				{
					if (animationcounter < 3 && animation)
					{
						avatartempvec[2].update(3);
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
							avatartempvec[2].speed(0);
							avatartempvec[2].moveright();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 1:
						{
							avatartempvec[2].speed(0);
							avatartempvec[2].moveleft();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 2:
						{
							avatartempvec[2].speed(0);
							avatartempvec[2].moveup();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						case 3:
						{
							avatartempvec[2].speed(0);
							avatartempvec[2].movedown();
							animationcounter++;
							countswitch++;

							animation = true;
						}
						break;
						}
				}
				else avatartempvec[2].setintrect(IntRect(138, 10, 40, 52));
			}


		}

		handlelevels(clock);

		if (frog.size() > 1)
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

	soundloader[0]->loadFromFile("Undertale-100-Megalovania.wav");
	soundloader[1]->loadFromFile("smb_world_clear.wav");

	winsprite.setTexture(*winscreen);
	winsprite.setTextureRect(IntRect(450, 211, 223, 210));
	winsprite.setOrigin(223/2, 210/2);
	winsprite.scale(2, 2);
	winsprite.setPosition(*gamewidth/2, *gameheight/2);


	losesprite.setTexture(*losescreen);
	losesprite.setTextureRect(IntRect(246, 54, 42, 57));
	losesprite.setOrigin(42 / 2, 57 / 2);
	losesprite.scale(5, 5);
	losesprite.setPosition(*gamewidth / 2, *gameheight / 2);

	logosprite.setTexture(*logoscreen);
	logosprite.setOrigin(788 / 2, 160 / 2);
	logosprite.setPosition(*gamewidth / 2, *gameheight / 2);

	nameoutput.setString("Name: ");
	nameoutput.setFont(titlefont);
	nameoutput.setPosition(0, 0);
	nameoutput.setCharacterSize(20);

	liveoutput.setString("Lives: ");
	liveoutput.setFont(titlefont);
	liveoutput.setPosition(7*(*gamewidth) / 8, 0);
	liveoutput.setCharacterSize(20);

	highscoreoutput.setString("Highscore: ");
	highscoreoutput.setFont(titlefont);
	highscoreoutput.setPosition(2 * (*gamewidth) / 8, 0);
	highscoreoutput.setCharacterSize(20);

	timeleft.setString("Time Left: ");
	timeleft.setFont(titlefont);
	timeleft.setPosition(5 * (*gamewidth) / 8, 0);
	timeleft.setCharacterSize(20);

	inputname.setFont(titlefont);
	inputname.setColor(Color::Black);
	inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
	inputname.setCharacterSize(12);

	smalltexture->loadFromFile("small.gif");
	largetexture->loadFromFile("buttons.png");
	background->loadFromFile("background.png");
	font.loadFromFile("zorque.ttf");
	titlefont.loadFromFile("KeepCalm-Medium.ttf");
	gametile->loadFromFile("gametile.png");

	hometexture->loadFromFile("homepage1.png");
	frogtexture[0]->loadFromFile("animals.jpeg.png");
	frogtexture[1]->loadFromFile("orange1.png");
	frogtexture[2]->loadFromFile("purple1.png");
	frogtexture[3]->loadFromFile("red1.png");
	frogtexture[4]->loadFromFile("blue1.png");


	avatartexture[0]->loadFromFile("Avatar1.png");
	avatartexture[1]->loadFromFile("Avatar2.png");
	avatartexture[2]->loadFromFile("Avatar3.png");

	temp->loadFromFile("background.png");
	temp1.setTexture(*temp);
	temp1.setTextureRect(IntRect(680, 375, 21, 19));
	temp1.setPosition(0, 0);
	temp1.setOrigin(10, 10);

	home.setbackground(*hometexture);
	home.setdim(dimensions);

	settingm.setbackground(*background);
	settingm.setnumber(3);
	settingm.setfont(titlefont);
	settingm.setdim(dimensions);
	settingm.setsubtitle(1, "Settings", 60, Color::Red, Vector2f(2, 10));
	settingm.setsubtitle(2, "Difficulty", 20, Color::Red, Vector2f(3.1, 4.5));
	settingm.setsubtitle(3, "Sound", 20, Color::Red, Vector2f(3.5, 2.5));
	//settingm.setsubtitle(4, "Volume", 20, Color::Red, Vector2f(3.5, 1.75));

	storymenu.setbackground(*background);
	storymenu.setfont(titlefont);
	storymenu.setnumber(2);
	storymenu.setdim(dimensions);

	singmulti.setbackground(*background);
	singmulti.setfont(titlefont);
	singmulti.setnumber(1);
	singmulti.setdim(dimensions);
	singmulti.setsubtitle(1, "Single or Multiplayer", 25, Color::Red, Vector2f(2, 10));


	namem.setbackground(*background);
	namem.setfont(titlefont);
	namem.setdim(dimensions);
	namem.setnumber(2);
	namem.setsubtitle(1, "Enter your name", 22, Color::Red, Vector2f(2.1, 10));
	namem.setsubtitle(2, "Choose a character", 22, Color::Red, Vector2f(2.1, 2));

	inputname.setFont(titlefont);
	inputname.setColor(Color::Black);
	inputname.setPosition(Vector2f(*gamewidth / 2, *gameheight / 4));
	inputname.setCharacterSize(12);

	creditm.setbackground(*background);
	creditm.setfont(titlefont);
	creditm.setnumber(2);
	creditm.setdim(dimensions);
	creditm.setsubtitle(1, "Credits", 60, Color::Red, Vector2f(2, 10));

	nextbutposition = new Vector2f;
	nextbutposition->x = *gamewidth / 1.6;
	nextbutposition->y = *gameheight / 1.25;

	nextbut.settexture(*largetexture, largenormal);
	nextbut.setdim(dimensions);
	nextbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	nextbut.setorigin();
	nextbut.setposition(nextbutposition);
	nextbut.settext("Next", 20, Color::Black);
	nextbut.loadfont(font);
	nextbut.sethovertexture(largehover, 0, 0);
	nextbut.hover(true);
	nextbut.magnify(true);

	playbut.settexture(*largetexture, largenormal);
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

	settingbut.settexture(*largetexture, largenormal);
	settingbut.setdim(dimensions);
	settingbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	settingbut.setorigin();
	settingbut.alignv(playbutposition, largebuttonheight);
	settingbut.settext("Settings", 20, Color::Black);
	settingbut.loadfont(font);
	settingbut.sethovertexture(largehover, 0, 0);
	settingbut.hover(true);
	settingbut.magnify(true);

	storybut.settexture(*largetexture, largenormal);
	storybut.setdim(dimensions);
	storybut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	storybut.setorigin();
	storybut.alignv((settingbut.returnpos()), largebuttonheight);
	storybut.settext("Story", 20, Color::Black);
	storybut.loadfont(font);
	storybut.sethovertexture(largehover, 0, 0);
	storybut.hover(true);
	storybut.magnify(true);

	highscorebut.settexture(*largetexture, largenormal);
	highscorebut.setdim(dimensions);
	highscorebut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	highscorebut.setorigin();
	highscorebut.alignv(storybut.returnpos(), largebuttonheight);
	highscorebut.settext("Highscore", 20, Color::Black);
	highscorebut.loadfont(font);
	highscorebut.sethovertexture(largehover, 0, 0);
	highscorebut.hover(true);
	highscorebut.magnify(true);

	creditsbut.settexture(*largetexture, largenormal);
	creditsbut.setdim(dimensions);
	creditsbut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	creditsbut.setorigin();
	creditsbut.alignv(highscorebut.returnpos(), largebuttonheight);
	creditsbut.settext("Credits", 20, Color::Black);
	creditsbut.loadfont(font);
	creditsbut.sethovertexture(largehover, 0, 0);
	creditsbut.hover(true);
	creditsbut.magnify(true);

	quitbut.settexture(*largetexture, largenormal);
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
	backbut.settexture(*largetexture, largenormal);
	backbut.setorigin();
	backbut.centerh(*gameheight / 1.010);
	backbut.loadfont(font);
	backbut.settext("Back", 25, Color::Black);
	backbut.sethovertexture(largehover, 0, 0);
	backbut.magnify(true);
	backbut.hover(true);

	easy.setdim(dimensions);
	easy.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	easy.settexture(*smalltexture, smallnormal);
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
	medium.settexture(*smalltexture, smallnormal);
	medium.setorigin();
	medium.alignh(easy.returnpos(), 1.5*smallbuttonwidth);
	medium.loadfont(font);
	medium.settext("M", 25, Color::Black);
	medium.hover(true);
	medium.sethovertexture(smallhover, 0, 0);
	medium.magnify(true);

	hard.setdim(dimensions);
	hard.setsize(Vector2f(smallbuttonwidth, smallbuttonheight));
	hard.settexture(*smalltexture, smallnormal);
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
	on.settexture(*smalltexture, smallnormal);
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
	off.settexture(*smalltexture, smallnormal);
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
	singlebut.settexture(*largetexture, largenormal);
	singlebut.setdim(dimensions);
	singlebut.setsize(Vector2f(largebuttonwidth, largebuttonheight));
	singlebut.setorigin();
	singlebut.settext("Single Player", 17, Color::Black);
	singlebut.loadfont(font);
	singlebut.sethovertexture(largehover, 0, 0);
	singlebut.hover(true);
	singlebut.magnify(true);

	multiplayerbut.settexture(*largetexture, largenormal);
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

	for (int i = 0; i < 8; i++)
		buttonvectotr.push_back(*buttonpointer);

	frogbutton = new Vector2f;

	frogbutton->x = *gamewidth / 3;
	frogbutton->y = *gameheight*0.6;

	buttonvectotr[0].setposition(frogbutton);
	buttonvectotr[1].setposition(&(*buttonvectotr[0].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[2].setposition(&(*buttonvectotr[1].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[3].setposition(&(*buttonvectotr[2].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[4].setposition(&(*buttonvectotr[3].returnpos() + sf::Vector2f(4 * image.x, 0)));
	buttonvectotr[5].setposition(&Vector2f(*gamewidth / 2.75, *gameheight*0.7));
	buttonvectotr[6].setposition(&(*buttonvectotr[5].returnpos() + sf::Vector2f(4 * 40, 0)));
	buttonvectotr[7].setposition(&(*buttonvectotr[6].returnpos() + sf::Vector2f(4 * 40, 0)));

	buttonvectotr[0].hover(true);
	buttonvectotr[1].hover(true);
	buttonvectotr[2].hover(true);
	buttonvectotr[3].hover(true);
	buttonvectotr[4].hover(true);
	buttonvectotr[5].hover(true);
	buttonvectotr[6].hover(true);
	buttonvectotr[7].hover(true);

	buttonvectotr[0].setsize(Vector2f(21, 19));
	buttonvectotr[1].setsize(Vector2f(21, 19));
	buttonvectotr[2].setsize(Vector2f(21, 19));
	buttonvectotr[3].setsize(Vector2f(21, 19));
	buttonvectotr[4].setsize(Vector2f(21, 19));
	buttonvectotr[5].setsize(Vector2f(40, 52));
	buttonvectotr[6].setsize(Vector2f(40, 52));
	buttonvectotr[7].setsize(Vector2f(40, 52));
	Player *frogtemp;

	frogtemp = new Player;

	Vector2f *gamedi;
	gamedi = new Vector2f;
	gamedi->x = *gamewidth;
	gamedi->y = *gameheight;

	frogtemp->gamedimension(gamedi);
	frogtemp->settexture(*frogtexture[0]);
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

	frogtempvec[0].settexture(*frogtexture[0]);
	frogtempvec[1].settexture(*frogtexture[1]);
	frogtempvec[2].settexture(*frogtexture[2]);
	frogtempvec[3].settexture(*frogtexture[3]);
	frogtempvec[4].settexture(*frogtexture[4]);

	frogtempvec[0].setpos(buttonvectotr[0].returnpos());
	frogtempvec[1].setpos(buttonvectotr[1].returnpos());
	frogtempvec[2].setpos(buttonvectotr[2].returnpos());
	frogtempvec[3].setpos(buttonvectotr[3].returnpos());
	frogtempvec[4].setpos(buttonvectotr[4].returnpos());

	for (int i = 0; i < 5; i++)
	{
		charint.push_back(oldrect);

	}
	avatartemp = new Player;
	avatartemp->gamedimension(gamedi);
	avatartemp->settexture(*avatartexture[0]);
	avatartemp->setintrect(IntRect(138, 10, 40, 52));

	avatar2temp = new Player;
	avatar2temp->gamedimension(gamedi);
	avatar2temp->settexture(*avatartexture[1]);
	avatar2temp->setintrect(IntRect(138, 10, 40, 52));

	avatar3temp = new Player;
	avatar3temp->gamedimension(gamedi);
	avatar3temp->settexture(*avatartexture[2]);
	avatar3temp->setintrect(IntRect(138, 10, 40, 52));


	avatartemp->setpos(buttonvectotr[5].returnpos());

	avatartemp->numofrtsprite(4);
	avatartemp->setrightrect(4, IntRect(10, 10, 40, 52));
	avatartemp->setrightrect(3, IntRect(74, 8, 40, 56));
	avatartemp->setrightrect(2, IntRect(202, 8, 40, 56));
	avatartemp->setrightrect(1, IntRect(138, 10, 40, 52));
	avatartemp->numofltsprite(4);
	avatartemp->setleftrect(4, IntRect(18, 74, 34, 52));
	avatartemp->setleftrect(3, IntRect(210, 72, 34, 54));
	avatartemp->setleftrect(2, IntRect(82, 72, 34, 54));
	avatartemp->setleftrect(1, IntRect(146, 74, 34, 52));
	avatartemp->numofupsprite(4);
	avatartemp->setuprect(4, IntRect(12, 202, 40, 52));
	avatartemp->setuprect(3, IntRect(76, 200, 40, 56));
	avatartemp->setuprect(1, IntRect(140, 202, 40, 52));
	avatartemp->setuprect(2, IntRect(204, 200, 40, 56));
	avatartemp->numofdownsprite(4);
	avatartemp->setdownrect(4, IntRect(10, 10, 40, 52));
	avatartemp->setdownrect(3, IntRect(74, 8, 40, 56));
	avatartemp->setdownrect(1, IntRect(138, 10, 40, 52));
	avatartemp->setdownrect(2, IntRect(202, 8, 40, 56));
	avatartemp->speed(0);


	avatar2temp->setpos(buttonvectotr[6].returnpos());
	avatar2temp->numofrtsprite(4);
	avatar2temp->setrightrect(4, IntRect(10, 10, 40, 52));
	avatar2temp->setrightrect(3, IntRect(74, 8, 40, 56));
	avatar2temp->setrightrect(2, IntRect(202, 8, 40, 56));
	avatar2temp->setrightrect(1, IntRect(138, 10, 40, 52));
	avatar2temp->numofltsprite(4);
	avatar2temp->setleftrect(4, IntRect(18, 74, 34, 52));
	avatar2temp->setleftrect(3, IntRect(210, 72, 34, 54));
	avatar2temp->setleftrect(2, IntRect(82, 72, 34, 54));
	avatar2temp->setleftrect(1, IntRect(146, 74, 34, 52));
	avatar2temp->numofupsprite(4);
	avatar2temp->setuprect(4, IntRect(12, 202, 40, 52));
	avatar2temp->setuprect(3, IntRect(76, 200, 40, 56));
	avatar2temp->setuprect(1, IntRect(140, 202, 40, 52));
	avatar2temp->setuprect(2, IntRect(204, 200, 40, 56));
	avatar2temp->numofdownsprite(4);
	avatar2temp->setdownrect(4, IntRect(10, 10, 40, 52));
	avatar2temp->setdownrect(3, IntRect(74, 8, 40, 56));
	avatar2temp->setdownrect(1, IntRect(138, 10, 40, 52));
	avatar2temp->setdownrect(2, IntRect(202, 8, 40, 56));
	avatar2temp->speed(0);

	avatar3temp->setpos(buttonvectotr[7].returnpos());
	avatar3temp->numofrtsprite(4);
	avatar3temp->setrightrect(4, IntRect(10, 10, 40, 52));
	avatar3temp->setrightrect(3, IntRect(74, 8, 40, 56));
	avatar3temp->setrightrect(2, IntRect(202, 8, 40, 56));
	avatar3temp->setrightrect(1, IntRect(138, 10, 40, 52));
	avatar3temp->numofltsprite(4);
	avatar3temp->setleftrect(4, IntRect(18, 74, 34, 52));
	avatar3temp->setleftrect(3, IntRect(210, 72, 34, 54));
	avatar3temp->setleftrect(2, IntRect(82, 72, 34, 54));
	avatar3temp->setleftrect(1, IntRect(146, 74, 34, 52));
	avatar3temp->numofupsprite(4);
	avatar3temp->setuprect(4, IntRect(12, 202, 40, 52));
	avatar3temp->setuprect(3, IntRect(76, 200, 40, 56));
	avatar3temp->setuprect(1, IntRect(140, 202, 40, 52));
	avatar3temp->setuprect(2, IntRect(204, 200, 40, 56));
	avatar3temp->numofdownsprite(4);
	avatar3temp->setdownrect(4, IntRect(10, 10, 40, 52));
	avatar3temp->setdownrect(3, IntRect(74, 8, 40, 56));
	avatar3temp->setdownrect(1, IntRect(138, 10, 40, 52));
	avatar3temp->setdownrect(2, IntRect(202, 8, 40, 56));
	avatar3temp->speed(0);


	avatartempvec.push_back(*avatartemp);
	avatartempvec.push_back(*avatar2temp);
	avatartempvec.push_back(*avatar3temp);
	//avatar2tempvec.push_back(*avatar2temp);
	//avatar3tempvec.push_back(*avatar3temp);

	avatartempvec[0].settexture(*avatartexture[0]);
	avatartempvec[1].settexture(*avatartexture[1]);
	avatartempvec[2].settexture(*avatartexture[2]);


	
}
void renderer(RenderWindow& window)
{
	window.clear(Color::Green);
	if (loadflag)
	{
		loadscreen->play(window, .2);
		loadflag = false;
	}
	
	if (homeflag &&!settingflag &&!storyflag &&!highscoreflag &&!creditflag&&!singlemultiflag)
	{
		home.render(window);
		void setscale(RenderWindow &);

		home.render(window);
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
		
		if (storyflag)
		{
			storyscreen->play(window, 5);
			storyflag = false;
			homeflag = true;
			//loadflag = false;
		}
		//storymenu.render(window);
		//backbut.render(window);
	}
	if (creditflag)
	{
		creditm.render(window);
		backbut.render(window); 
		window.draw(logosprite);
		for (int i = 5; i < 8; i++)
		{
			buttonvectotr[i].render(window);
			avatartempvec[i - 5].render(window);
		}
	}
	if (singlemultiflag)
	{
		singmulti.render(window);
		backbut.render(window);
		singlebut.render(window);
		multiplayerbut.render(window);

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
		window.draw(temp1);
		nextbut.render(window);
		window.draw(temp1);

	}

	if (gameflag&&!win&&!lose)
	{
		
		if (frog.size()>1)
			window.setView(view2);

		one->render(window);

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

			one->render(window);

			for (int i = 0; i < enemy.size(); i++)
			for (int j = 0; j < enemy[i].size(); j++)
				enemy[i][j].render(window);

			for (int i = 0; i < helper.size(); i++)
			for (int j = 0; j < helper[i].size(); j++)
				helper[i][j].render(window);

			frog[1].render(window);
			frog[0].render(window);
		}
		window.draw(nameoutput);
		window.draw(liveoutput);
		window.draw(timeleft);
		window.draw(highscoreoutput);
	}

	if (win && gameflag)
	{
		gameflag = false;
		window.draw(winsprite);
		
	}
	if (lose && gameflag)
	{
		gameflag = false;
		window.draw(losesprite);
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

	for (int i = 0; i < buttonvectotr.size(); i++)
		buttonvectotr[i].setscale(dimensions);

	frogbutton->x = *gamewidth / 3;
	frogbutton->y = *gameheight*0.6;

	for (int i = 0; i < frogtempvec.size(); i++)
		frogtempvec[i].scale(dimensions);


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
	if (!keypressed && clock.getElapsedTime().asSeconds() > 15)
		lives--, clock.restart();

	if (!keypressed2 && clock.getElapsedTime().asSeconds() > 15)
		lives2--, clock.restart();

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

			if (k == 0)
				lives--;
			else lives2--;

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


	if (clock2.getElapsedTime().asSeconds() > .1)
	{


		for (int j = 0; j < enemy[0].size(); j++)
			enemy[0][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][j] * enemyspeedfactor);

		for (int j = 0; j < enemy[1].size(); j++)
			enemy[1][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][3 + j] * enemyspeedfactor);

		for (int j = 0; j < enemy[2].size(); j++)
			enemy[2][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][6 + j] * enemyspeedfactor);

		for (int j = 0; j < enemy[3].size(); j++)
			enemy[3][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][9 + j] * enemyspeedfactor);

		for (int j = 0; j < enemy[4].size(); j++)
			enemy[4][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][11 + j] * enemyspeedfactor);

		for (int j = 0; j < enemy[5].size(); j++)
			enemy[5][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][13 + j] * enemyspeedfactor);

		for (int j = 0; j < enemy[6].size(); j++)
			enemy[6][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[1][15 + j] * enemyspeedfactor);

		/*for (int i = 0; i < enemy.size(); i++)
		{
		for (int j = 0; j < enemy[i].size(); j++)
		enemy[i][j].speed(scalefactor->x*clock.getElapsedTime().asSeconds() * speed[1][i*enemy[i].size() + j] * enemyspeedfactor);
		}*/

		for (int j = 0; j < helper[0].size(); j++)
			helper[0][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[2][j] * helperspeedfactor);

		for (int j = 0; j < helper[1].size(); j++)
			helper[1][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[2][1 + j] * helperspeedfactor);

		for (int j = 0; j < helper[2].size(); j++)
			helper[2][j].speed(scalefactor->x*clock2.getElapsedTime().asSeconds() * speed[2][3 + j] * helperspeedfactor);


		/*	for (int i = 0; i < helper.size(); i++)
		{
		for (int j = 0; j < helper[i].size(); j++)
		helper[i][j].speed(scalefactor->x*clock.getElapsedTime().asSeconds() * speed[2][i*helper[i].size() + j] * helperspeedfactor);
		}*/

		/*for (int i = 0; i < frog.size(); i++)
		{
		frog[i].speed(10*clock.getElapsedTime().asSeconds() * speed[0][i]*playerspeedfactor);
		}
		*/

		clock2.restart();

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

				if (i == 0)
					lives--;
				else lives2--;
			}

		}

		for (int i = 0; i < frog.size(); i++)
		for (int j = 0; j < winpos.size(); j++)
		{
			if (obstacle.boundary(frog[i], winpos[j].left, winpos[j].top, winpos[j].width, winpos[j].height)
				&& animationcounter == 0)
			{
				win = true;
			}
	
		}

		if (lives == 0)
			lose = true;

		if (!keypressed)
		{
			if (!obstacle.boundary(frog[0], *gamewidth - speed[0][0] * 4, 0, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveright();
				keypressed = true;
				clock.restart();

			}

			if (!obstacle.boundary(frog[0], 0, 0, 3 * speed[0][0], *gameheight/**scalefactor->y*/))
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveleft();
				keypressed = true;
				clock.restart();

			}

			if (!obstacle.boundary(frog[0], 0, 0, *gamewidth/**scalefactor->y*/, 3 * speed[0][0]))
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveup();
				keypressed = true;
				clock.restart();
				highscore += 20;
				highscoreoutput.setString("Highscore: " + to_string(highscore));
			}

			if (!obstacle.boundary(frog[0], 0, *gameheight - 3 * speed[0][0]/**scalefactor->y*/, *gamewidth, *gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				frog[0].speed(speed[0][0]);
				frog[0].movedown();
				keypressed = true;
				clock.restart();
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
	liveoutput.setString("Lives: "+to_string(lives));
	timeleft.setString("Time Left: " + to_string(clock.getElapsedTime().asSeconds()));
}

void setlevel1()
{

	int enemycol = 3;
	int enemyrow = 5;

	/*
	Vector2f *gamedim;
	gamedim = new Vector2f;
	gamedim->x = gamewidth;
	gamedim->y = gameheight;
	*/
	vector<Enemy> enem;
	Enemy *enemytemp;

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(585, 101, 99, 58));
	enemytemp->setleftrect(1, IntRect(601, 169, 99, 58));

	for (int i = 0; i < 3; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(5, 487, 108, 58));
	enemytemp->setleftrect(1, IntRect(467, 141, 108, 58));

	for (int i = 0; i < 3; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(583, 53, 100, 37));
	enemytemp->setleftrect(1, IntRect(583, 5, 100, 37));

	for (int i = 0; i < 3; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(262, 143, 83, 54));
	enemytemp->setleftrect(1, IntRect(161, 143, 83, 54));

	for (int i = 0; i < 2; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(298, 57, 107, 54));
	enemytemp->setleftrect(1, IntRect(511, 489, 107, 56));

	for (int i = 0; i < 2; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(7, 7, 98, 55));
	enemytemp->setleftrect(1, IntRect(357, 143, 98, 55));

	for (int i = 0; i < 2; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	enemytemp = new Enemy;

	enemytemp->settexture(*gametile);
	enemytemp->repeated(true);
	enemytemp->gamedimension(gamedim);
	enemytemp->setrandom();
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->numofrtsprite(1);
	enemytemp->numofltsprite(1);
	enemytemp->setrightrect(1, IntRect(18, 394, 119, 50));
	//enemytemp->setrightrect(2, IntRect(167, 395, 119, 50));
	//enemytemp->setrightrect(3, IntRect(316, 396, 119, 50));
	//enemytemp->setrightrect(4, IntRect(465, 394, 119, 50));

	enemytemp->setleftrect(1, IntRect(8, 265, 119, 50));
	//enemytemp->setleftrect(2, IntRect(157, 266, 119, 50));
	//enemytemp->setleftrect(3, IntRect(306, 265, 119, 50));
	//enemytemp->setleftrect(4, IntRect(455, 264, 119, 50));

	for (int i = 0; i < 2; i++)
		enem.push_back(*enemytemp);

	enemy.push_back(enem);
	enem.clear();

	vector<float> speedtemp(17, 1);

	speedtemp[0] = 1.5;
	speedtemp[1] = 1.5;
	speedtemp[2] = 2;

	speedtemp[3] = 1.5;
	speedtemp[4] = 2;
	speedtemp[5] = 2;


	speedtemp[6] = 1.5;
	speedtemp[7] = 2;
	speedtemp[8] = 2;


	speedtemp[9] = 2;
	speedtemp[10] = 2;

	speedtemp[11] = 1.5;
	speedtemp[12] = 2;

	speedtemp[13] = 3.5;
	speedtemp[14] = 3.5;

	speedtemp[15] = 1.5;
	speedtemp[16] = 2.5;

	speed.push_back(speedtemp);

	enemyposition = new Vector2f;

	((enemyposition))->x = *gamewidth / 2;
	((enemyposition))->y = *gameheight*.85;

	enemy[0][0].setpos(enemyposition, &Vector2f(0, 0));

	enemychange = new Vector2f*[17];

	for (int i = 0; i < 17; i++)
		enemychange[i] = new Vector2f;


	enemychange[0] = &Vector2f(0, 0);

	enemychange[1]->x = *gamewidth*.9 - ((enemyposition))->x;
	enemychange[1]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[2]->x = *gamewidth / 8 - ((enemyposition))->x;
	enemychange[2]->y = -*gameheight*.1;//- ((enemyposition))->y;

	for (int j = 0; j < enemy[0].size(); j++)
		enemy[0][j].setpos(enemyposition, enemychange[j]);

	enemychange[3]->x = *gamewidth*.3 - ((enemyposition))->x;
	enemychange[3]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[4]->x = *gamewidth * 3 / 8 - ((enemyposition))->x;
	enemychange[4]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[5]->x = 0 - ((enemyposition))->x;
	enemychange[5]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[1].size(); j++)
		enemy[1][j].setpos(enemyposition, enemychange[3 + j]);

	enemychange[6]->x = *gamewidth*.1 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[7]->x = *gamewidth * 5 / 8 - ((enemyposition))->x;
	enemychange[7]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[8]->x = *gamewidth / 2 - ((enemyposition))->x;
	enemychange[8]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[2].size(); j++)
		enemy[2][j].setpos(enemyposition, enemychange[6 + j]);

	enemychange[9]->x = *gamewidth * 7 / 8 - ((enemyposition))->x;
	enemychange[9]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[10]->x = *gamewidth / 4 - ((enemyposition))->x;
	enemychange[10]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[3].size(); j++)
		enemy[3][j].setpos(enemyposition, enemychange[9 + j]);

	enemychange[11]->x = *gamewidth *.7 - ((enemyposition))->x;
	enemychange[11]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[12]->x = *gamewidth * 3 / 4 - ((enemyposition))->x;
	enemychange[12]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[4].size(); j++)
		enemy[4][j].setpos(enemyposition, enemychange[11 + j]);

	enemychange[13]->x = *gamewidth / 4 - ((enemyposition))->x;// - ((enemyposition))->x;
	enemychange[13]->y = *gameheight*.55 - ((enemyposition))->y;

	enemychange[14]->x = *gamewidth*.75 - ((enemyposition))->x;
	enemychange[14]->y = *gameheight*.55 - ((enemyposition))->y;

	for (int j = 0; j < enemy[4].size(); j++)
		enemy[5][j].setpos(enemyposition, enemychange[13 + j]);

	enemychange[15]->x = *gamewidth * 7 / 12 - ((enemyposition))->x;
	enemychange[15]->y = *gameheight*.35 - ((enemyposition))->y;

	enemychange[16]->x = *gamewidth * 11 / 24 - ((enemyposition))->x;
	enemychange[16]->y = *gameheight*.25 - ((enemyposition))->y;

	for (int j = 0; j < enemy[6].size(); j++)
		enemy[6][j].setpos(enemyposition, enemychange[15 + j]);
	/*for (int i = 0; i < enemy.size(); i++)
	for (int j = 0; j < enemy[i].size(); j++)
	{
	enemy[i][j].setpos(enemyposition, enemychange[i*enemy[i].size()+j]);
	}*/

	int helpercol = 6;
	int helperrow = 1;

	vector<Helper> help;
	Helper *helptemp;


	helptemp = new Helper;


	(helptemp)->settexture(*gametile);
	//(helptemp)->setintrect(IntRect(5, 148, 56, 34));
	(helptemp)->numofrtsprite(1);
	(helptemp)->setrightrect(1, IntRect(246, 5, 180, 39));
	(helptemp)->numofltsprite(1);
	(helptemp)->setleftrect(1, IntRect(246, 5, 180, 39));
	(helptemp)->repeated(true);
	(helptemp)->gamedimension(gamedim);
	(helptemp)->setrandom();


	for (int j = 0; j < 1; j++)
	{
		help.push_back(*helptemp);
	}

	helper.push_back(help);
	help.clear();

	helptemp = new Helper;


	(helptemp)->settexture(*gametile);
	//(helptemp)->setintrect(IntRect(5, 148, 56, 34));
	(helptemp)->numofrtsprite(1);
	(helptemp)->setrightrect(1, IntRect(436, 5, 137, 39));
	(helptemp)->numofltsprite(1);
	(helptemp)->setleftrect(1, IntRect(436, 5, 137, 39));
	(helptemp)->repeated(true);
	(helptemp)->gamedimension(gamedim);
	(helptemp)->setrandom();

	for (int j = 0; j < 2; j++)
	{
		help.push_back(*helptemp);
	}

	helper.push_back(help);
	help.clear();

	(helptemp)->settexture(*gametile);
	//(helptemp)->setintrect(IntRect(5, 148, 56, 34));
	(helptemp)->numofrtsprite(1);
	(helptemp)->setrightrect(1, IntRect(253, 490, 52, 26));
	(helptemp)->numofltsprite(1);
	(helptemp)->setleftrect(1, IntRect(322, 489, 51, 26));
	(helptemp)->repeated(true);
	(helptemp)->gamedimension(gamedim);
	(helptemp)->setrandom();

	for (int j = 0; j < 7; j++)
	{
		help.push_back(*helptemp);
	}

	helper.push_back(help);
	help.clear();

	speedtemp.resize(10);

	helperposition = new Vector2f;
	((helperposition))->x = *gamewidth / 8;
	((helperposition))->y = *gameheight*.25;

	//help[0].setpos(helperposition, &Vector2f(0, 0));

	helperchange = new Vector2f*[10];

	for (int i = 0; i < 10; i++)
		helperchange[i] = new Vector2f;

	helper[0][0].setpos(enemyposition, &Vector2f(0, 0));

	helperchange[0] = &Vector2f(0, 0);

	for (int j = 0; j < helper[0].size(); j++)
		helper[0][j].setpos(helperposition, helperchange[j]);

	helperchange[1]->x = *gamewidth / 12 - ((helperposition))->x;
	helperchange[1]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[2]->x = *gamewidth / 2 - ((helperposition))->x;
	helperchange[2]->y = *gameheight*.15 - ((helperposition))->y;

	for (int j = 0; j < helper[1].size(); j++)
		helper[1][j].setpos(helperposition, helperchange[1 + j]);


	helperchange[3]->x = *gamewidth / 3 - ((helperposition))->x;
	helperchange[3]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[4]->x = *gamewidth / 3 + 51 - ((helperposition))->x;
	helperchange[4]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[5]->x = *gamewidth * 10 / 12 - ((helperposition))->x;
	helperchange[5]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[6]->x = *gamewidth * 10 / 12 + 51 - ((helperposition))->x;
	helperchange[6]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[7]->x = *gamewidth * 19 / 24 - ((helperposition))->x;
	helperchange[7]->y = *gameheight*.25 - ((helperposition))->y;

	helperchange[8]->x = *gamewidth - 51 - ((helperposition))->x;
	helperchange[8]->y = *gameheight*.15 - ((helperposition))->y;

	helperchange[9]->x = *gamewidth - ((helperposition))->x;
	helperchange[9]->y = *gameheight*.15 - ((helperposition))->y;

	for (int j = 0; j < helper[2].size(); j++)
		helper[2][j].setpos(helperposition, helperchange[3 + j]);



	//for (int i = 0; i < helpercol - 1; i++)
	//	helperchange[i] = new Vector2f;

	/*helperchange[0]->x = 0 - (helperposition)->x;
	helperchange[0]->y = gamedim[1][0] * .25 - gamedim[1][0] * .15;

	helperchange[1]->x = gamedim[0][0] * 3 / 4 - (helperposition)->x;
	helperchange[1]->y = gamedim[1][0] * .25 - gamedim[1][0] * .15;

	helperchange[2]->x = 0 - (helperposition)->x;
	helperchange[2]->y = gamedim[1][0] * .35 - gamedim[1][0] * .15;

	helperchange[3]->x = gamedim[0][0] / 3 - (helperposition)->x;
	helperchange[3]->y = gamedim[1][0] * .35 - gamedim[1][0] * .15;

	helperchange[4]->x = gamedim[0][0] * 2 / 3 - (helperposition)->x;
	helperchange[4]->y = gamedim[1][0] * .35 - gamedim[1][1] * .15;


	for (int i = 1; i < help.size(); i++)
	{
	help[i].setpos(helperposition, helperchange[i - 1]);
	}*/


	speedtemp[0] = 2.5;

	speedtemp[1] = 1.5;
	speedtemp[2] = 2.5;

	speedtemp[3] = 1.5;
	speedtemp[4] = 1.5;
	speedtemp[5] = 1.5;
	speedtemp[6] = 1.5;
	speedtemp[7] = 2.5;
	speedtemp[8] = 4;
	speedtemp[9] = 4;
	//speedtemp[5] = 1;

	speed.push_back(speedtemp);

	vector<vector<arraypos>> temp;
	vector <arraypos> tempdirec;

	tempdirec.push_back(arraypos(0, 0));
	tempdirec.push_back(arraypos(0, 1));
	tempdirec.push_back(arraypos(1, 0));
	tempdirec.push_back(arraypos(2, 0));
	tempdirec.push_back(arraypos(4, 0));
	tempdirec.push_back(arraypos(5, 0));
	tempdirec.push_back(arraypos(5, 1));
	tempdirec.push_back(arraypos(6, 1));

	temp.push_back(tempdirec);

	tempdirec.clear();
	tempdirec.push_back(arraypos(0, 2));
	tempdirec.push_back(arraypos(1, 1));
	tempdirec.push_back(arraypos(1, 2));
	tempdirec.push_back(arraypos(2, 1));
	tempdirec.push_back(arraypos(2, 2));
	tempdirec.push_back(arraypos(3, 0));
	tempdirec.push_back(arraypos(3, 1));
	tempdirec.push_back(arraypos(4, 1));
	tempdirec.push_back(arraypos(6, 0));


	temp.push_back(tempdirec);

	direction.push_back(temp);

	temp.clear();
	tempdirec.clear();


	tempdirec.push_back(arraypos(0, 0));
	tempdirec.push_back(arraypos(2, 4));

	temp.push_back(tempdirec);
	tempdirec.clear();

	tempdirec.push_back(arraypos(1, 0));
	tempdirec.push_back(arraypos(2, 0));
	tempdirec.push_back(arraypos(2, 1));
	tempdirec.push_back(arraypos(2, 3));
	tempdirec.push_back(arraypos(2, 2));
	tempdirec.push_back(arraypos(1, 1));
	tempdirec.push_back(arraypos(2, 5));
	tempdirec.push_back(arraypos(2, 6));


	temp.push_back(tempdirec);

	direction.push_back(temp);

	temp.clear();
	tempdirec.clear();

	waterpos.push_back(IntRect(0, *gameheight / 10, *gamewidth, *gameheight*.4));

	winpos.push_back(IntRect(0, 0, *gamewidth, *gameheight*.1));

}
void setlevel1resolution(RenderWindow& window, Level& levelone)
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

	gamescaledim->x = (*gamewidth);
	gamescaledim->y = (*gameheight);


	//fullscreen = false;
	levelone.levelscale(gamescaledim);
	frog[0].scale(gamescaledim);

	if (frog.size() > 1)
	{
		frog[1].scale(gamescaledim);
		speed[0][1] = (*gameheight *.10) / 3;

	}
	speed[0][0] = (*gameheight *.10) / 3;

	//Vector2f *position3;

	// = new Vector2f;



	Vector2f* helperscale;
	helperscale = new Vector2f;
	helperscale->x = gamedim[0][0] / oldgamedim->x;
	helperscale->y = gamedim[1][0] / oldgamedim->y;


	helperposition = new Vector2f;
	((helperposition))->x = *gamewidth / 8;
	((helperposition))->y = *gameheight*.25;


	helperchange[0] = &Vector2f(0, 0);

	for (int j = 0; j < helper[0].size(); j++)
		helper[0][j].setpos(helperposition, helperchange[j]);

	helperchange[1]->x = *gamewidth / 12 - ((helperposition))->x;
	helperchange[1]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[2]->x = *gamewidth / 2 - ((helperposition))->x;
	helperchange[2]->y = *gameheight*.15 - ((helperposition))->y;

	for (int j = 0; j < helper[1].size(); j++)
		helper[1][j].setpos(helperposition, helperchange[1 + j]);


	helperchange[3]->x = *gamewidth / 3 - ((helperposition))->x;
	helperchange[3]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[4]->x = *gamewidth / 3 + 51 - ((helperposition))->x;
	helperchange[4]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[5]->x = *gamewidth * 10 / 12 - ((helperposition))->x;
	helperchange[5]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[6]->x = *gamewidth * 10 / 12 + 51 - ((helperposition))->x;
	helperchange[6]->y = *gameheight*.35 - ((helperposition))->y;

	helperchange[7]->x = *gamewidth * 19 / 24 - ((helperposition))->x;
	helperchange[7]->y = *gameheight*.25 - ((helperposition))->y;

	helperchange[8]->x = *gamewidth - 51 - ((helperposition))->x;
	helperchange[8]->y = *gameheight*.15 - ((helperposition))->y;

	helperchange[9]->x = *gamewidth - ((helperposition))->x;
	helperchange[9]->y = *gameheight*.15 - ((helperposition))->y;

	for (int j = 0; j < helper[2].size(); j++)
		helper[2][j].setpos(helperposition, helperchange[3 + j]);
	/*for (int j = 0; j < helper[2].size(); j++)
	helper[0][j].setpos(helperposition, helperchange[3 + j]);*/

	/*helper[0][0].setpos(helperposition, &Vector2f(0, 0));
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
	*/
	for (int i = 0; i < helper.size(); i++)
	for (int j = 1; j < helper[i].size(); j++)
		helper[i][j].scale(helperscale);

	helper[0][0].scale(helperscale);

	(enemyposition)->x = *gamewidth / 2;
	(enemyposition)->y = *gameheight*.85;


	enemychange[0] = &Vector2f(0, 0);

	enemychange[1]->x = *gamewidth*.9 - ((enemyposition))->x;
	enemychange[1]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[2]->x = *gamewidth / 8 - ((enemyposition))->x;
	enemychange[2]->y = -*gameheight*.1;//- ((enemyposition))->y;

	for (int j = 0; j < enemy[0].size(); j++)
		enemy[0][j].setpos(enemyposition, enemychange[j]);

	enemychange[3]->x = *gamewidth*.3 - ((enemyposition))->x;
	enemychange[3]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[4]->x = *gamewidth * 3 / 8 - ((enemyposition))->x;
	enemychange[4]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[5]->x = 0 - ((enemyposition))->x;
	enemychange[5]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[1].size(); j++)
		enemy[1][j].setpos(enemyposition, enemychange[3 + j]);

	enemychange[6]->x = *gamewidth*.1 - ((enemyposition))->x;
	enemychange[6]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[7]->x = *gamewidth * 5 / 8 - ((enemyposition))->x;
	enemychange[7]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[8]->x = *gamewidth / 2 - ((enemyposition))->x;
	enemychange[8]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[2].size(); j++)
		enemy[2][j].setpos(enemyposition, enemychange[6 + j]);

	enemychange[9]->x = *gamewidth * 7 / 8 - ((enemyposition))->x;
	enemychange[9]->y = *gameheight*.75 - ((enemyposition))->y;

	enemychange[10]->x = *gamewidth / 4 - ((enemyposition))->x;
	enemychange[10]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[3].size(); j++)
		enemy[3][j].setpos(enemyposition, enemychange[9 + j]);

	enemychange[11]->x = *gamewidth *.7 - ((enemyposition))->x;
	enemychange[11]->y = *gameheight*.85 - ((enemyposition))->y;

	enemychange[12]->x = *gamewidth * 3 / 4 - ((enemyposition))->x;
	enemychange[12]->y = *gameheight*.65 - ((enemyposition))->y;

	for (int j = 0; j < enemy[4].size(); j++)
		enemy[4][j].setpos(enemyposition, enemychange[11 + j]);

	enemychange[13]->x = *gamewidth / 4 - ((enemyposition))->x;// - ((enemyposition))->x;
	enemychange[13]->y = *gameheight*.55 - ((enemyposition))->y;

	enemychange[14]->x = *gamewidth*.75 - ((enemyposition))->x;
	enemychange[14]->y = *gameheight*.55 - ((enemyposition))->y;

	for (int j = 0; j < enemy[4].size(); j++)
		enemy[5][j].setpos(enemyposition, enemychange[13 + j]);

	enemychange[15]->x = *gamewidth * 7 / 12 - ((enemyposition))->x;
	enemychange[15]->y = *gameheight*.35 - ((enemyposition))->y;

	enemychange[16]->x = *gamewidth * 11 / 24 - ((enemyposition))->x;
	enemychange[16]->y = *gameheight*.25 - ((enemyposition))->y;

	for (int j = 0; j < enemy[6].size(); j++)
		enemy[6][j].setpos(enemyposition, enemychange[15 + j]);
	/*for (int j = 0; j < enemy[6].size(); j++)
	enemy[6][j].setpos(enemyposition, enemychange[15 + j]);*/
	/*enemy[0][0].setpos(enemyposition, &Vector2f(0, 0));

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

	*/
	Vector2f *enemyscale;
	enemyscale = new Vector2f;
	enemyscale->x = gamedim[0][0] / oldgamedim->x;
	enemyscale->y = gamedim[1][0] / oldgamedim->y;

	/*for (int i = 1; i < enemy[0].size(); i++)
	{
	enemy[0][i].setpos(enemyposition, enemychange[i - 1]);
	}
	*/

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

	levelone.levelscale(gamed);

	scalefactor->x = gamedim[0][0] / oldgamedim->x;
	scalefactor->y = gamedim[1][0] / oldgamedim->y;

	for (int i = 0; i < waterpos.size(); i++)
	{
		waterpos[i].width *= scalefactor->x;
		waterpos[i].height *= scalefactor->y;
	}

	for (int i = 0; i < winpos.size(); i++)
	{
		winpos[i].width *= scalefactor->x;
		winpos[i].height *= scalefactor->y;
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

void loadstoryint()
{
	loadintrectstory[0] = IntRect(1, 1, 223, 209);
	loadintrectstory[1] = IntRect(225, 1, 224, 209);
	loadintrectstory[2] = IntRect(1, 211, 223, 210);

	loadintrectstory[3] = IntRect(1, 422, 223, 209);
	loadintrectstory[4] = IntRect(225, 211, 224, 210);
	loadintrectstory[5] = IntRect(450, 1, 224, 209);

	loadintrectstory[6] = IntRect(450, 211, 223, 210);


	/*loadintrectstory[7] = IntRect(345, 414, 331, 195);
	loadintrectstory[8] = IntRect(686, 414, 331, 195);

	loadintrectstory[9] = IntRect(5, 619, 331, 195);
	loadintrectstory[10] = IntRect(345, 619, 331, 195);
	loadintrectstory[11] = IntRect(686, 619, 331, 195);

	loadintrectstory[12] = IntRect(5, 824, 331, 195);
	*/
}

void loadscreenint()
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
