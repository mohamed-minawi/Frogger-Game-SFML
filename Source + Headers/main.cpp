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

IntRect n(150,143, 105, 40);
IntRect h(264, 144, 105, 40);
IntRect pressed(131, 195, 51, 51);
IntRect hover(186, 195, 51, 51);
IntRect initial(239, 195, 51, 51);
int gamewidth=780;
int gameheight=580;
Vector2f *oldgamedim;

#define buttonwidth 105
#define buttonheight 40
Texture *carpicpointer;
bool keypressed = false, keypressed2 = false;
int animationcounter=0, animationcounter2=0, levelcount=1;
float enemyspeedfactor = 1, helperspeedfactor = 1, playerspeedfactor=1;
int lives = 7;
Vector2f* helperposition, **helperchange;
Vector2f *scalefactor;

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

Vector2f *gamedim;
Vector2f *frogposition;

void handlelevels(Clock&);

void setlevel1();
void setlevel1resolution(RenderWindow&, Level&);


void main()
{
	RenderWindow window(VideoMode(gamewidth, gameheight), "Mitcho buttons");
	Texture hometexture,buttexture, gametext;

	frog.reserve(2);

	Font font;
	bool homeflag = true, setflag = false, helpflag = false, gameflag = false;

	button play, settingbut, easy,medium,hard, helpbut, back, on,off;
	menu home, settingm,helpm, game;
	

	hometexture.loadFromFile("homepage.jpg");
	buttexture.loadFromFile("buttons.jpg");
	font.loadFromFile("waltograph42.otf");
	gametext.loadFromFile("Map.png");
	
	gamedim = new Vector2f;
	*gamedim=Vector2f(gamewidth, gameheight);

	play.setdim(&Vector2f(gamewidth, gameheight));
	play.setsize(Vector2f(buttonwidth, buttonheight));
	play.settexture(buttexture,n);
	play.setorigin();
	play.setposition(&Vector2f(gamewidth/2, 200));
	play.loadfont(font);
	play.settext("Play", 25, Color::Black);
	play.sethovertexture(h, 105, 40);
	play.magnify(true);
	play.hover(true);

	settingbut.setdim(&Vector2f(gamewidth, gameheight));
	settingbut.setsize(Vector2f(buttonwidth, buttonheight));
	settingbut.settexture(buttexture, n);
	settingbut.setorigin();
	settingbut.alignv(play.returnpos(), 60);
	settingbut.loadfont(font);
	settingbut.settext("Settings", 25, Color::Black);
	settingbut.sethovertexture(h, 105, 40);
	settingbut.magnify(true);
	settingbut.hover(true);

	helpbut.setdim(&Vector2f(gamewidth, gameheight));
	helpbut.setsize(Vector2f(buttonwidth, buttonheight));
	helpbut.settexture(buttexture, n);
	helpbut.setorigin();
	helpbut.alignv(play.returnpos(), 120);
	helpbut.loadfont(font);
	helpbut.settext("Help", 25, Color::Black);
	helpbut.sethovertexture(h, 105, 40);
	helpbut.hover(true);
	helpbut.magnify(true);

	back.setdim(&Vector2f(gamewidth, gameheight));
	back.setsize(Vector2f(buttonwidth, buttonheight));
	back.settexture(buttexture, n);
	back.setorigin();
	back.setposition(&Vector2f(700, 200));
	back.loadfont(font);
	back.settext("Back", 25, Color::Black);
	back.sethovertexture(h, 105, 40);
	back.magnify(true);
	back.hover(true);
	
	easy.setdim(&Vector2f(gamewidth, gameheight));
	easy.setsize(Vector2f(51, 51));
	easy.settexture(buttexture, initial);
	easy.setorigin();
	easy.setposition(&Vector2f(gamewidth / 2, 200));
	easy.alignh(easy.returnpos(), -80);
	easy.loadfont(font);
	easy.settext("E", 25, Color::Black);
	easy.hover(true);
	easy.sethovertexture(hover, 51, 51); 
	easy.magnify(true);

	medium.setdim(&Vector2f(gamewidth, gameheight));
	medium.setsize(Vector2f(51, 51));
	medium.settexture(buttexture, pressed);
	medium.setorigin();
	medium.alignh(easy.returnpos(), 80);
	medium.loadfont(font);
	medium.settext("M", 25, Color::Black);
	medium.hover(true);
	medium.sethovertexture(hover, 51, 51);
	medium.magnify(true);

	hard.setdim(&Vector2f(gamewidth, gameheight));
	hard.setsize(Vector2f(51, 51));
	hard.settexture(buttexture, initial);
	hard.setorigin();
	hard.alignh(medium.returnpos(), 80);
	hard.loadfont(font);
	hard.settext("H", 25, Color::Black);
	hard.hover(true);
	hard.sethovertexture(hover, 51, 51);
	hard.magnify(true);

	on.setdim(&Vector2f(gamewidth, gameheight));
	on.setsize(Vector2f(51, 51));
	on.settexture(buttexture, pressed);
	on.setorigin();
	on.alignv(easy.returnpos(), 80);
	on.loadfont(font);
	on.settext("ON", 25, Color::Black);
	on.hover(true);
	on.sethovertexture(hover, 51, 51);
	on.magnify(true);

	off.setdim(&Vector2f(gamewidth, gameheight));
	off.setsize(Vector2f(51, 51));
	off.settexture(buttexture, pressed);
	off.setorigin();
	off.alignh(on.returnpos(), 80);
	off.loadfont(font);
	off.settext("OFF", 25, Color::Black);
	off.hover(true);
	off.sethovertexture(hover, 51, 51);
	off.magnify(true);

	home.setbackground(hometexture);
	settingm.setbackground(hometexture);
	settingm.setfont(font);
	settingm.setnumber(2);
	settingm.setsubtitle(1, "Difficulty", 20, Color::Black, Vector2f(190, (play.returnpos()->y) - 10));
	settingm.setsubtitle(2, "Sounds", 20, Color::Black, Vector2f(190, on.returnpos()->y - 10));
	helpm.setbackground(hometexture);
	game.setbackground(gametext);

	Texture animal;

	animal.loadFromFile("animals.jpeg.png");

	Player *frogtemp;

	frogtemp = new Player;

	frogtemp->gamedimension(gamedim);
	frogtemp->settexture(animal);
	frogtemp->setintrect(IntRect(229, 235, 23, 20));

	
	frogposition = new Vector2f;
	frogposition->x = gamewidth / 2;
	frogposition->y = gameheight *.95;


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


	///Vector2f((gamedim->y / 10) / y, (gamedim->y / 20) / y)
	///////////////////////

	delete frogtemp;
	frogtemp = NULL;

	vector<float> speedtemp;

	speedtemp.push_back((gameheight*.15));
	///////////////////////////
	//	speedtemp.push_back(20);
	///////////////////////////
	speed.push_back(speedtemp);

	speedtemp.clear();

	Texture carpic;
	carpic.loadFromFile("Car.png");
	
	carpicpointer = &carpic;
	//Enemy car[9];

	//for (int i = 0; i < 9; i++)
	//{
	//	car[i].settexture(carpic);
	//	//car.setintrect(IntRect(5, 148, 56, 34));
	//	car[i].numofrtsprite(1);
	//	car[i].setrightrect(1, IntRect(5, 148, 56, 34));

	//	car[i].numofltsprite(1);
	//	car[i].setleftrect(1, IntRect(5, 148, 56, 34));

	//	car[i].repeated(true);
	//	car[i].setrandom(gamewidth, gameheight);
	//}

	//car[0].setpos(Vector2f(200, 500 - 17));
	//car[0].speed(.25);

	//car[1].setpos(Vector2f(400, 500 - 17));
	//car[1].speed(.25);

	//car[2].setpos(Vector2f(600, 500 - 17));
	//car[2].speed(.25);

	//car[3].setpos(Vector2f(800, 500 - 17));
	//car[3].speed(.25);

	//car[4].setpos(Vector2f(260, 450 - 17));
	//car[4].speed(.5);

	//car[5].setpos(Vector2f(520, 450 - 17));
	//car[5].speed(.5);

	//car[6].setpos(Vector2f(780, 450 - 17));
	//car[6].speed(.5);

	//car[7].setpos(Vector2f(0, 400 - 17));
	//car[7].speed(.75);

	//car[8].setpos(Vector2f(400, 400 - 17));
	//car[8].speed(.75);
	//
	//Helper log[6];

	//for (int i = 0; i < 6; i++)
	//{
	//	log[i].settexture(carpic);
	//	//log.setintrect(IntRect(5, 148, 56, 34));
	//	log[i].numofrtsprite(1);
	//	log[i].setrightrect(1, IntRect(5, 148, 56, 34));

	//	log[i].numofltsprite(1);
	//	log[i].setleftrect(1, IntRect(5, 148, 56, 34));

	//	log[i].repeated(true);
	//	log[i].setrandom(gamewidth, gameheight);
	//}

	//log[0].setpos(Vector2f(400, 150));
	//log[0].speed(.7);

	//log[1].setpos(Vector2f(0, 210 ));
	//log[1].speed(.4);

	//log[2].setpos(Vector2f(600,210 ));
	//log[2].speed(.4);

	//log[3].setpos(Vector2f(780, 270));
	//log[3].speed(.1);

	//log[4].setpos(Vector2f(260, 270));
	//log[4].speed(.1);

	//log[5].setpos(Vector2f(520, 270));
	//log[5].speed(.1);


	Clock clock;
		
	/*bool keypressed = false, multiplayer = false;*/
	/*int count=0;*/

	View view1, view2;

	view1.setViewport(FloatRect(0, 0, .5, 1));
	view1.setSize(gamewidth / 2, gameheight);

	view2.setViewport(FloatRect(.5, 0, .5, 1));
	view2.setSize(gamewidth / 2, gameheight);

	Vector2f position(gamewidth / 2, gameheight / 2), position2(position);

	view1.setCenter(gamewidth / 2, gameheight / 2);
	view2.setCenter(gamewidth / 2, gameheight / 2);
	
	oldgamedim = new Vector2f;

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;

	setlevel1();

	//helper[0][0].scalefirst(&Vector2f((gamedim->y / 10) / 20, (gamedim->y / 20) / 20));
	Vector2f *fulldim;

	fulldim = new Vector2f;

	fulldim->x = 1360;
	fulldim->y = 770;

	Level one("level1.txt");
	one.setgamedim(fulldim);
	frog[0].gamedimension(fulldim);

	/*for (int i = 0; i < helper.size(); i++)
	for (int j = 0; j < helper[i].size(); j++)
	{
		helper[i][j].scale(fulldim);
	}*/

	window.create(VideoMode(500 , 500), "Mitcho Buttons");
	
//	gamewidth = window.getSize().x;
//	gameheight = window.getSize().y;
//
//	*gamedim = Vector2f(gamewidth, gameheight);
//
//	frogposition->x = gamewidth / 2;
//	frogposition->y = gameheight *.95;
//
//	//fullscreen = false;
//	one.levelscale(gamedim);
//	frog[0].scale(gamedim);
//	speed[0][0] = (gameheight *.10) / 3;
//	
//	//Vector2f *position3;
//
//	// = new Vector2f;
//
//	(helperposition)->x = gamewidth / 2;
//	(helperposition)->y = gameheight*.15;
//
//	helper[0][0].setpos(helperposition, &Vector2f(0, 0));
//	helperchange[0]->x = 0 - gamedim->x / 2;
//	helperchange[0]->y = gamedim->y*.25 - gamedim->y*.15;
//
//	helperchange[1]->x = gamedim->x - gamedim->x / 2;
//	helperchange[1]->y = gamedim->y*.25 - gamedim->y*.15;
//
//	helperchange[2]->x = 0 - gamedim->x / 2;
//	helperchange[2]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	helperchange[3]->x = gamedim->x / 2 - gamedim->x / 2;
//	helperchange[3]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	helperchange[4]->x = gamedim->x - gamedim->x / 2;
//	helperchange[4]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	Vector2f *helperscale;
//	helperscale = new Vector2f;
//	helperscale->x = gamedim->x / oldgamedim->x;
//	helperscale->y = gamedim->y / oldgamedim->y;
//
//	//helper[0][0].scale(helperscale);
//
//	for (int i = 1; i < helper[0].size(); i++)
//	{
//		helper[0][i].setpos(helperposition, helperchange[i - 1]);
//	}
//
//	
//	/*for (int i = 0; i < helper.size(); i++)
//	for (int j = 0; j < helper[i].size(); j++)
//	{
//		helper[i][j].scale(gamedim);
//	}*/
//
//
//	for (int i = 0; i < helper.size(); i++)
//	for (int j = 1; j < helper[i].size(); j++)
//		helper[i][j].scale(helperscale);//temp);//helperscale);//helper[0][0].returnscale());
//	
//	
//
//
//	helper[0][0].scale(helperscale);//temp);
//
//	//window.create(VideoMode(800, 770), "Mitcho Buttons");
//
//	gamewidth = window.getSize().x;
//	gameheight = window.getSize().y;
//
//	*gamedim = Vector2f(gamewidth, gameheight);
//
//	speed[0][0] = (gameheight *.10)/3;
//
//	
//
//	frogposition->x = gamewidth / 2;
//	frogposition->y = gameheight *.95;
//
//	//fullscreen = false;
//	one.levelscale(gamedim);
//	frog[0].scale(gamedim);
//
//	
//	(helperposition)->x = gamewidth / 2;
//	(helperposition)->y = gameheight*.15;
//
//	helper[0][0].setpos(helperposition, &Vector2f(0, 0));
//
//	helperchange[0]->x = 0 - gamedim->x / 2;
//	helperchange[0]->y = gamedim->y*.25 - gamedim->y*.15;
//
//	helperchange[1]->x = gamedim->x - gamedim->x / 2;
//	helperchange[1]->y = gamedim->y*.25 - gamedim->y*.15;
//
//	helperchange[2]->x = 0 - gamedim->x / 2;
//	helperchange[2]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	helperchange[3]->x = gamedim->x / 2 - gamedim->x / 2;
//	helperchange[3]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	helperchange[4]->x = gamedim->x - gamedim->x / 2;
//	helperchange[4]->y = gamedim->y*.35 - gamedim->y*.15;
//
//	
//	helperscale = new Vector2f;
//	helperscale->x = gamedim->x / oldgamedim->x;
//	helperscale->y = gamedim->y / oldgamedim->y;
//
//
//	for (int i = 1; i < helper[0].size(); i++)
//	{
//		helper[0][i].setpos(helperposition, helperchange[i - 1]);
//	}
//	
//	//helper[0][0].scale(helperscale);
//
//	/*for (int i = 0; i < helper.size(); i++)
//	for (int j = 1; j < helper[i].size(); j++)
//		helper[i][j].scale(helperscale);//helper[0][0].returnscale());
//*/
//	//helper[0][0].scale(helperscale);

	//one.levelscale(gamedim);


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
				homeflag = true;
				setflag = false;
			}
			if (event.type == Event::MouseButtonPressed)
			{	Vector2i ml = Mouse::getPosition(window);
				if (settingbut.ifhover(ml))
				{ 
					homeflag = false;
					setflag = true;
				}
				if (back.ifhover(ml))
				{
					homeflag = true;
					setflag = false;
					helpflag = false;
				}
				if (helpbut.ifhover(ml))
				{
					homeflag = false;
					helpflag = true;
				}
				if (play.ifhover(ml))
				{
					homeflag = false;
					gameflag = true;
				}
			}

			if (play.ifhover(mp))
			{
				play.hoverchange();
			}
			else play.returntooriginal();

			if (back.ifhover(mp))
			{
				back.hoverchange();
			}
			else back.returntooriginal();

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

		}

		//setlevel1direction();
		//for (int i = 0; i < 9; i++)
		//if (obstacle.ifmet(frog, car[i]))
		//{
		//	frog.setintrect(IntRect(229, 235, 23, 20));

		//	frog.setpos(Vector2f(gamewidth / 2, gameheight - 20-17));

		//	//obstacle.playermovewithhelper(frog, car);
		//}

		//for (int i = 0; i < 6; i++)
		//if (obstacle.ifmet(frog, log[i]))
		//{
		//	obstacle.playermovewithhelper(frog, log[i]);
		//}
		///*else if (obstacle.boundary(frog,0, 100, gamewidth, 270))
		//{
		//	frog.setintrect(IntRect(229, 235, 23, 20));

		//	frog.setpos(Vector2f(gamewidth / 2, gameheight - 20 - 17));
		//}
		//*/
		//if (clock.getElapsedTime().asSeconds()>.1)
		//{
		//	for (int i = 0; i < 9; i++)
		//		car[i].speed(clock.getElapsedTime().asSeconds() * 5);
		//	clock.restart();
		//	
		//	if (keypressed&&count<3)
		//	{
		//		frog.update(3);
		//		count++;
		//	}
		//	else
		//	{
		//		count = 0;
		//		keypressed = false;
		//	}

		//	if (!keypressed)
		//	{
		//		if (Keyboard::isKeyPressed(Keyboard::Right))
		//		{
		//			frog.moveright();
		//			keypressed = true;
		//			
		//		}
		//		if (Keyboard::isKeyPressed(Keyboard::Left))
		//		{
		//			frog.moveleft();
		//			keypressed = true;

		//		}
		//		if (Keyboard::isKeyPressed(Keyboard::Up))
		//		{
		//			frog.moveup();
		//			keypressed = true;
		//		}
		//		if (Keyboard::isKeyPressed(Keyboard::Down))
		//		{
		//			frog.movedown();
		//			keypressed = true;
		//		}
		//	}
		//	
		//}

		//for (int i = 0; i < 9; i++)
		//{
		//	if (i<4||i>6)
		//	car[i].moveright();
		//	else car[i].moveleft();

		//}


		//for (int i = 0; i < 6; i++)
		//{
		//	if (i<1 || i>2)
		//		log[i].moveright();
		//	else log[i].moveleft();

		//}

		handlelevels(clock);

		if (frog.size()>1)
		{
			if (frog[0].returnpos()->x >= view2.getSize().x / 2 && frog[0].returnpos()->x <= 3 * gamewidth / 4)
				position.x = frog[0].returnpos()->x;

			if (frog[1].returnpos()->x >= view1.getSize().x / 2 && frog[1].returnpos()->x <= 3 * gamewidth / 4)
				position2.x = frog[1].returnpos()->x;

			view1.setCenter(position2);
			view2.setCenter(position);
		}
		/*view1.reset(FloatRect(position.x, position.y, gamewidth/2, gameheight));
		view2.reset(FloatRect(position.x, position.y, gamewidth / 2, gameheight));
		*/
		
		/*view1.reset(FloatRect(position.x, position.y, gamewidth/2, gameheight));
		view2.reset(FloatRect(position.x, position.y, gamewidth / 2, gameheight));
*/

		window.clear();
		//back.render(window);
		if (homeflag &&!setflag&&!helpflag)
		{
			home.render(window);
			play.render(window);
			settingbut.render(window);
			helpbut.render(window);
			back.render(window);

		}
		if (setflag &&!homeflag&&!helpflag)
		{
			settingm.render(window);
			easy.render(window);
			medium.render(window);
			hard.render(window);
			back.render(window);
			on.render(window);
			off.render(window);

		}
		if (helpflag &&!setflag&&!homeflag)
		{
			//settingm.render(window);
			back.render(window);
		}

		if (gameflag &!homeflag)
		{

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
			}
		}
		window.display();

	}

}

void setlevel1()
{

	int enemycol = 9;
	int enemyrow = 1;


	Vector2f *gamedim;
	gamedim = new Vector2f;
	gamedim->x = gamewidth;
	gamedim->y = gameheight;

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
	enemytemp->setrandom(FloatRect(0,gameheight/2,gamewidth,gameheight*.9));

	for (int i = 0; i < enemycol; i++)
	{
		enem.push_back(*enemytemp);
	}

	enem[0].setpos(&Vector2f(200, gameheight*.85));

	enem[1].setpos(&Vector2f(400, gameheight*.85));

	enem[2].setpos(&Vector2f(600, gameheight*.85));

	enem[3].setpos(&Vector2f(800, gameheight*.85));

	enem[4].setpos(&Vector2f(260, gameheight*.75));
	speedtemp[4] = 1;

	enem[5].setpos(&Vector2f(520, gameheight*.75));
	speedtemp[5] = 1;

	enem[6].setpos(&Vector2f(780, gameheight*.75));
	speedtemp[6] = 1;

	enem[7].setpos(&Vector2f(0, gameheight*.65));
	speedtemp[7] = 1.5;

	enem[8].setpos(&Vector2f(400, gameheight*.65));
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
	((helperposition))->x = gamewidth / 2;
	((helperposition))->y = gameheight*.15;

	help[0].setpos(helperposition, &Vector2f(0,0));

	helperchange = new Vector2f*[helpercol-1];

	for (int i = 0; i < helpercol - 1; i++)
		helperchange[i] = new Vector2f;

	helperchange[0]->x = 0 - gamedim->x / 2;
	helperchange[0]->y = gamedim->y*.25 - gamedim->y*.15;

	helperchange[1]->x = gamedim->x - gamedim->x / 2;
	helperchange[1]->y = gamedim->y*.25 - gamedim->y*.15;

	helperchange[2]->x = 0 - gamedim->x / 2;
	helperchange[2]->y = gamedim->y*.35 - gamedim->y*.15;

	helperchange[3]->x = gamedim->x / 2 - gamedim->x / 2;
	helperchange[3]->y = gamedim->y*.35 - gamedim->y*.15;

	helperchange[4]->x = gamedim->x - gamedim->x / 2;
	helperchange[4]->y = gamedim->y*.35 - gamedim->y*.15;


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

	waterpos.push_back(IntRect(0, gameheight/10, gamewidth, gameheight*.4));
}

void handlelevels(Clock& clock)
{
	///////////////////////
	///////////////////////

	//NEED TO ADD TIME CONDITION

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

			frog[k].setpos(&Vector2f(gamewidth / 2, gameheight*.95));

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
		if (obstacle.ifmet(frog[k], helper[i][j]))
		{
			obstacle.playermovewithhelper(frog[k], helper[i][j]);
		}
	}


	if (clock.getElapsedTime().asSeconds() > .1)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			for (int j = 0; j < enemy[i].size(); j++)
				enemy[i][j].speed(clock.getElapsedTime().asSeconds() * speed[1][i*enemy[i].size() + j] * enemyspeedfactor);
		}

		for (int i = 0; i < helper.size(); i++)
		{
			for (int j = 0; j < helper[i].size(); j++)
				helper[i][j].speed(clock.getElapsedTime().asSeconds() * speed[2][i*helper[i].size() + j] * helperspeedfactor);
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
			
		if (keypressed2&& animationcounter2<3&&frog.size()>1)
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

		//for (int i = 0; i < frog.size(); i++)
		//for (int j = 0; j < waterpos.size(); j++)
		//{
		//	/*if (obstacle.boundary(frog[i], waterpos[j].left, waterpos[j].top, waterpos[j].width, waterpos[j].height)
		//		&& animationcounter == 0)*/
		//	{	for (int k = 0; k < helper.size(); k++)
		//			for (int l = 0; l < helper[k].size(); l++)
		//			if (obstacle.ifmet(frog[i], helper[k][l]))
		//				{
		//				water = true;
		//				}
		//	}
		//	/*if (obstacle.boundary(frog[i], waterpos[j].left, waterpos[j].top, waterpos[j].width, waterpos[j].height)
		//		&& animationcounter == 0)*/
		//	if (!water)
		//	{
		//		frog[i].setintrect(IntRect(229, 235, 23, 20));

		//		frog[i].setpos(&Vector2f(gamewidth / 2, gameheight*.95));
		//	}

		//	water = false;

		//}

		
		if (!keypressed)
		{
			if (!obstacle.boundary(frog[0], gamewidth - speed[0][0], 0, gamewidth, gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveright();
				keypressed = true;

			}

			if (!obstacle.boundary(frog[0], 0, 0, speed[0][0], gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveleft();
				keypressed = true;

			}

			if (!obstacle.boundary(frog[0], 0, 0, gamewidth, speed[0][0]))
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				frog[0].speed(speed[0][0]);
				frog[0].moveup();
				keypressed = true;
			}

			if (!obstacle.boundary(frog[0], 0, gameheight - speed[0][0], gamewidth, gameheight))
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				frog[0].speed(speed[0][0]);
				frog[0].movedown();
				keypressed = true;
			}
		}
		if (frog.size() > 1 && !keypressed2)
		{

			if (!obstacle.boundary(frog[1], gamewidth - speed[0][1], 0, gamewidth, gameheight))
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					frog[1].speed(speed[0][1]);
					frog[1].moveright();
					keypressed2 = true;

				}
			
			if (!obstacle.boundary(frog[1], 0, 0, speed[0][1], gameheight))
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					frog[1].speed(speed[0][1]);
					frog[1].moveleft();
					keypressed2 = true;

				}
			if (!obstacle.boundary(frog[1], 0, 0, gamewidth, speed[0][1] * 3))
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					frog[1].speed(speed[0][1]);
					frog[1].moveup();
					keypressed2 = true;
				}


			if (!obstacle.boundary(frog[1], 0, gameheight - speed[0][1], gamewidth, gameheight))
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

void setlevel1resolution(RenderWindow& window, Level& one)
{
	gamewidth = window.getSize().x;
	gameheight = window.getSize().y;

	frogposition->x = gamewidth / 2;
	frogposition->y = gameheight *.95;

	*gamedim = Vector2f(gamewidth, gameheight);

	//fullscreen = false;
	one.levelscale(gamedim);
	frog[0].scale(gamedim);
	speed[0][0] = (gameheight *.10) / 3;

	//Vector2f *position3;

	// = new Vector2f;

	(helperposition)->x = gamewidth / 2;
	(helperposition)->y = gameheight*.15;

	helper[0][0].setpos(helperposition, &Vector2f(0, 0));

	helperchange[0]->x = 0 - gamedim->x / 2;
	helperchange[0]->y = gamedim->y*.25 - gamedim->y*.15;

	helperchange[1]->x = gamedim->x - gamedim->x / 2;
	helperchange[1]->y = gamedim->y*.25 - gamedim->y*.15;

	helperchange[2]->x = 0 - gamedim->x / 2;
	helperchange[2]->y = gamedim->y*.35 - gamedim->y*.15;

	helperchange[3]->x = gamedim->x / 2 - gamedim->x / 2;
	helperchange[3]->y = gamedim->y*.35 - gamedim->y*.15;

	helperchange[4]->x = gamedim->x - gamedim->x / 2;
	helperchange[4]->y = gamedim->y*.35 - gamedim->y*.15;

	Vector2f *helperscale;
	helperscale = new Vector2f;
	helperscale->x = gamedim->x / oldgamedim->x;
	helperscale->y = gamedim->y / oldgamedim->y;

	for (int i = 1; i < helper[0].size(); i++)
	{
		helper[0][i].setpos(helperposition, helperchange[i - 1]);
	}


	for (int i = 0; i < helper.size(); i++)
	for (int j = 1; j < helper[i].size(); j++)
		helper[i][j].scale(helperscale);//temp);//helperscale);//helper[0][0].returnscale());

	//helper[0][0].scale(helperscale);//temp);

	////window.create(VideoMode(800, 770), "Mitcho Buttons");

	//gamewidth = window.getSize().x;
	//gameheight = window.getSize().y;

	//*gamedim = Vector2f(gamewidth, gameheight);

	//speed[0][0] = (gameheight *.10) / 3;



	//frogposition->x = gamewidth / 2;
	//frogposition->y = gameheight *.95;

	////fullscreen = false;
	//one.levelscale(gamedim);
	//frog[0].scale(gamedim);


	//(helperposition)->x = gamewidth / 2;
	//(helperposition)->y = gameheight*.15;

	//helper[0][0].setpos(helperposition, &Vector2f(0, 0));

	//helperchange[0]->x = 0 - gamedim->x / 2;
	//helperchange[0]->y = gamedim->y*.25 - gamedim->y*.15;

	//helperchange[1]->x = gamedim->x - gamedim->x / 2;
	//helperchange[1]->y = gamedim->y*.25 - gamedim->y*.15;

	//helperchange[2]->x = 0 - gamedim->x / 2;
	//helperchange[2]->y = gamedim->y*.35 - gamedim->y*.15;

	//helperchange[3]->x = gamedim->x / 2 - gamedim->x / 2;
	//helperchange[3]->y = gamedim->y*.35 - gamedim->y*.15;

	//helperchange[4]->x = gamedim->x - gamedim->x / 2;
	//helperchange[4]->y = gamedim->y*.35 - gamedim->y*.15;


	//helperscale = new Vector2f;
	//helperscale->x = gamedim->x / oldgamedim->x;
	//helperscale->y = gamedim->y / oldgamedim->y;


	//for (int i = 1; i < helper[0].size(); i++)
	//{
	//	helper[0][i].setpos(helperposition, helperchange[i - 1]);
	//}

	//helper[0][0].scale(helperscale);

	/*for (int i = 0; i < helper.size(); i++)
	for (int j = 1; j < helper[i].size(); j++)
	helper[i][j].scale(helperscale);//helper[0][0].returnscale());
	*/
	helper[0][0].scale(helperscale);

	one.levelscale(gamedim);

	oldgamedim->x = window.getSize().x;
	oldgamedim->y = window.getSize().y;

}