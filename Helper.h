#ifndef Helper_h
#define Helper_h
#include "SFML\Graphics.hpp"
using namespace sf;
using namespace std;

class Helper
{
public:
	Helper();

	void settexture(Texture&);
	void setintrect(IntRect&);
	void setpos(Vector2f*, Vector2f*);

	void numofrtsprite(int);
	void numofltsprite(int);
	void numofupsprite(int);
	void numofdownsprite(int);

	/*void sizeright(float, float);
	void sizeleft(float, float);
	void sizeup(float, float);
	void sizedown(float, float);*/

	void setrightrect(int, IntRect&);
	void setleftrect(int, IntRect&);
	void setuprect(int, IntRect&);
	void setdownrect(int, IntRect&);

	void moveright();
	void moveleft();
	void moveup();
	void movedown();

	void speed(float);
	Vector2f* returnpos();

	void repeated(bool);
	void repeattime(float);
	void repeatrandom(bool);
	void setrandom();

	bool ifmove();
	Vector2f playermove();
	Vector2f returnsize();
	void rotate(float);

	void render(RenderWindow &);
	void gamedimension(float**);
	void scalefirst(Vector2f*);

	void scale(Vector2f*);
	Vector2f* returnscale();

private:
	IntRect *r, *l, *u, *d;
	int right = 0, left = 0, up = 0, down = 0;
	float x, y, xr, yr, xl, yl, xu, yu, xd, yd;
	int movecount = 0;
	float helperspeed = 20;
	Sprite helper;
	Vector2f *positionofother, *position, *changeinpos, *scalefactor, old, update;
	Texture *texture;
	IntRect *intrect;
	bool repeat = false, random = false;
	Clock clock;
	Time time;
	float repeatnum = 1;
	//Sprite helpers[6];
	float gamewidth = 500;
	float gamelength = 500;
	Vector2f  *currentscale;
	bool setinitialscale = false;
	float scalefactorx=1, scalefactory=1;
	float **gamedim;

	bool movright=false, movleft=false, movup=false, movdown=false;

	Vector2f size;
};
#endif
//#include "Helper.cpp"
