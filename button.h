#ifndef button_h
#define button_h

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <string>
#include <iostream>
using namespace sf;
using namespace std;

class button
{
public:

	button();
	void settexture(Texture&, IntRect);
	void settexture(Texture&);
	void settexture(IntRect&);
	void setcolor(Color);
	void settext(string,int,Color);
	void setorigin();
	void alignh(Vector2f*, float);
	void alignv(Vector2f*, float);
	void centerh(float);
	void centerv(float);
	void setposition(Vector2f*);
	Vector2f* returnpos();
	void render(RenderWindow&);
	void loadfont(Font);
	void setsize(Vector2f);
	void setdim(Vector2f*);
	void hover(bool);
	bool ifhover(Vector2i);
	void sethovertexture(IntRect&, int, int);
	void sethovertexture(Texture&, IntRect&, int, int);
	void sethovertexture(Texture&);
	void hoverchange();
	void magnify(bool);
	void returntooriginal();
	void setscale(Vector2f*);
	//void setscale(int, int, int, int, Vector2f&);
	
private:
	float *gameheight, *gamewidth, charsize;
	int buttonwidth, buttonheight;
	Text txt;
	Font font;
	Sprite but;
	Texture *textureoriginal, *texturenew;
	IntRect intrectoringinal, *intrectnew;
	bool hovers, magn, intrectt, intrecti, scale = false, ch=false,cv=false,ah=false,av=false,sp=false;
	int xn, yn;
	Vector2f *position;
	float difference;
	float scalefactorx, scalefactory;
	
	
};

#endif 
