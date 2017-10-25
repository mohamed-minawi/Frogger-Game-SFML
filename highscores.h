#ifndef highscores_h
#define highscores_h
#include "SFML\Graphics.hpp"
#include <string>
#include <fstream>
#include <vector>
using namespace sf;
using namespace std;
class highscores{
public:
	highscores();
	//void filename(string);
	void copy();
	void sort(int);
	void sort(int, int);
	void file(string);
	int find(string, int);
	void copytofile(int);
	void copytofile(int, int);
	void sendelements(int, string);
	void sendelements(int, int);
	void sendelements(int, float);
	void sendelements(int, double);
	void sendelements(int, char);
	void numofelements(int);
	Text display(int);
private:
	string *s;
	vector<string*> highscore;
	string e = "", filename, e1;
	int vectorpos, numofe;
	string round(string);

};
#endif
//#include "highscores.cpp"