#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Level.h"

using namespace sf;
using namespace std;

Level::Level(string sub)
{
	filename = sub; 
	
	texture = new Texture;
	
	texture->loadFromFile("spritesheet.png");

	intrect = new IntRect[5];
	
	intrect[0] = IntRect{ 5, 5, 685, 77 };
	intrect[1] = IntRect{ 5, 92, 685, 77 };
	intrect[2] = IntRect{ 5, 179, 685, 77 };
	intrect[3] = IntRect{ 6, 266, 685, 77 };
	intrect[4] = IntRect{ 6, 353, 685, 77 };
	
}
Level::~Level()
{
	delete	loader;
	delete tilelevel;
	delete gamedim;
	delete texture;
	delete intrect;
	delete scalefactorx;
	delete scalefactory;
	
	loader=NULL;
	tilelevel=NULL;
	gamedim=NULL;
	texture=NULL;
	intrect=NULL;
	scalefactorx = NULL;
	scalefactory = NULL;


}
void Level::setgamedim(Vector2f* dim)
{
	gamedim = new Vector2f;

	gamedim->x= dim->x;
	gamedim->y = dim->y;

	readfile();
	setarray();
}

void Level::readfile()
{
	ifstream inputf;
	inputf.open(filename);
	
	loader = new int*[10];

	for (int i = 0; i < 10; i++)
	{
		*(loader+i) = new int[2];
	}
	
	int k = 0,  j = 0;

	while (!inputf.eof() && k<10)
	{

		inputf >> loader[k][j];

		j++;

		if (j >= 2)
		{
			j = 0;
			k++;
		}
	}
		
		inputf.close();
}
void Level::setarray()
{
	tilelevel = new Sprite*[10];

	for (int i = 0; i < 10; i++)
	{
		tilelevel[i] = new Sprite[2];
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tilelevel[i][j].setTexture(*texture);

			switch (loader[i][j])
			{
			case grass:
			{ tilelevel[i][j].setTextureRect(intrect[0]); 
			tilelevel[i][j].setOrigin(intrect[0].width / 2, intrect[0].height / 2);
			}
				break;
			case roadleft:
			{tilelevel[i][j].setTextureRect(intrect[1]);
			tilelevel[i][j].setOrigin(intrect[1].width / 2, intrect[1].height / 2);
			}
				break;

			case roadright:
			{tilelevel[i][j].setTextureRect(intrect[2]);
			tilelevel[i][j].setOrigin(intrect[2].width / 2, intrect[2].height / 2);
			}
				break;
			case waterleft:
			{tilelevel[i][j].setTextureRect(intrect[3]);
			tilelevel[i][j].setOrigin(intrect[3].width / 2, intrect[3].height / 2);
			}
				break;
			case waterright:
			{tilelevel[i][j].setTextureRect(intrect[4]);
			tilelevel[i][j].setOrigin(intrect[4].width / 2, intrect[4].height / 2);
			}
				break;
			}
		}
	}

	setposition();
}


void Level::setposition()
{
	tilelevel[0][0].setPosition(gamedim->x / 4, gamedim->y*0.95);
	tilelevel[0][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.95);
	tilelevel[1][0].setPosition(gamedim->x / 4, gamedim->y*0.85);
	tilelevel[1][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.85);
	tilelevel[2][0].setPosition(gamedim->x / 4, gamedim->y*0.75);
	tilelevel[2][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.75);
	tilelevel[3][0].setPosition(gamedim->x / 4, gamedim->y*0.65);
	tilelevel[3][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.65);
	tilelevel[4][0].setPosition(gamedim->x / 4, gamedim->y*0.55);
	tilelevel[4][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.55);
	tilelevel[5][0].setPosition(gamedim->x / 4, gamedim->y*0.45);
	tilelevel[5][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.45);
	tilelevel[6][0].setPosition(gamedim->x / 4, gamedim->y*0.35);
	tilelevel[6][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.35);
	tilelevel[7][0].setPosition(gamedim->x / 4, gamedim->y*0.25);
	tilelevel[7][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.25);
	tilelevel[8][0].setPosition(gamedim->x / 4, gamedim->y*0.15);
	tilelevel[8][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.15);
	tilelevel[9][0].setPosition(gamedim->x / 4, gamedim->y*0.05);
	tilelevel[9][1].setPosition(gamedim->x * 3 / 4, gamedim->y*0.05);
}
void Level::levelscale(Vector2f* dim)
{
	scalefactorx = new float;
	scalefactory = new float;

	*scalefactorx = gamedim->x / dim->x;
	*scalefactory = gamedim->y / dim->y;
	gamedim->y=dim->y;
	gamedim->x = dim->x;
	
	tilelevel[0][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[0][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[1][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[1][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[2][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[2][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[3][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[3][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[4][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[4][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[5][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[5][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[6][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[6][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[7][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[7][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[8][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[8][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[9][0].scale(1 / (*scalefactorx), 1 / (*scalefactory));
	tilelevel[9][1].scale(1 / (*scalefactorx), 1 / (*scalefactory));

	setposition();
}


void Level::render(RenderWindow& window)
{
	for (int i = 0; i < 10;i++)
	for (int j = 0; j < 2; j++)
		window.draw(tilelevel[i][j]);
}