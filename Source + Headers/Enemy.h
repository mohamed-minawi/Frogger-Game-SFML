#ifndef Enemy_h
#define Enemy_h
#include "SFML\Graphics.hpp"
using namespace sf;
using namespace std;

class Enemy
{
public:
	Enemy();

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

	void rotate(float);
	void scale(Vector2f*);

	void repeated(bool);
	void repeattime(float);
	void repeatrandom(bool);
	void setrandom();

	void render(RenderWindow &);

	Vector2f returnsize();
	void gamedimension(float**);


	Vector2f* returnscale();


private:
	IntRect *r, *l, *u, *d;
	int right=0, left=0, up=0, down=0;
	float x, y, xr, yr, xl,yl,xu,yu,xd, yd;
	int movecount=0;
	float enemyspeed=20;
	 
	Sprite enemy;
	Vector2f *position;
	Vector2f *positionofother, *changeinpos;
	Texture *texture;
	IntRect* intrect;
	bool repeat=false, random=false;
	Clock clock;
	Time time;
	float repeatnum=1;
	//Sprite enemys[6];
	float gamewidth=500;
	float gamelength=500;
	float scalefactorx=1, scalefactory=1;
	bool setinitialscale = false;
	
	Vector2f  *scalefactor, old, update, *currentscale;
	FloatRect *repeatdimension;

	bool movright=false, movleft=false, movup=false, movdown=false;

	Vector2f size;

	float **gamedim;
};
#endif
//#include "Enemy.cpp"
