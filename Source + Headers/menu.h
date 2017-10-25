#ifndef menu_h
#define menu_h
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class menu
{
public:
	menu();
	void setbackground(Texture&);
	//void settitle(Texture, string, Vector2f);
	void setsubtitle(int, string , int , Color , Vector2f );
	void setfont(Font);
	void render(RenderWindow &);
	void setnumber(int);
	void setscale(Vector2f*);
	void setdim(Vector2f*);
	

private:
	
	int index;
	int elemnum;
	Sprite  background;
	float scalefactorx, scalefactory;
	float *gamewidth, *gameheight;
	Text subtitle[10];
	Font font;
	void settext(Text, int);
	Vector2f position[10];
	int charsize [10];
	Vector2f *menupos;
};

#endif 
