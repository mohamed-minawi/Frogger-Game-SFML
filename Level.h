#ifndef Level_h
#define Level_h

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class Level
{
public:
	Level(std::string);
	Level();
	~Level();

	void render(RenderWindow &);
	void setgamedim(Vector2f*);
	void levelscale(Vector2f*);

private:
	enum tiles{grass, roadleft, roadright, waterleft,waterright};
	void readfile(); 
	void setarray();
	void setposition();

	int **loader;
	Sprite **tilelevel;
	string filename;
	Vector2f *gamedim;
	Texture *texture;
	IntRect *intrect;
	float *scalefactorx, *scalefactory;
		/*gr{ 5, 5, 685, 77 };
	IntRect *roadl{ 5, 92, 685, 77 };
	IntRect *roadr{ 5, 179, 685, 77 };
	IntRect *waterl{ 6, 266, 685, 77 };
	IntRect *waterr{ 6, 353, 685, 77 };
	*/





};

#endif

//#include "Level.cpp"
