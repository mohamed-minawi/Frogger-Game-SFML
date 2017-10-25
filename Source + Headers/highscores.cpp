#include "highscores.h"
#include "SFML\Graphics.hpp"
#include <string>
using namespace sf;
using namespace std;

highscores::highscores(){}

void highscores::copy(){
		ifstream output;
		output.open(filename.c_str);
		int count = 0;
		output >> e1;
		while (!output.eof())
		{
			if (count < numofe)
			{
				*(s+count) = e1;
				output >> e1;
				count++;
			}

			else
			{
				count = 0;
				highscore.push_back(s);
			}
			
		}
		output.close();

	}
void highscores::sort(int elementnum)
{

	for (int i = 0; i < highscore.size(); i++)
	for (int j = i + 1; j < highscore.size(); j++)
	{
		if (atof(*(highscore[j] + elementnum - 1)) > atof(*(highscore[i] + elementnum - 1)))
		{
			f = highscore[i];
			highscore[i] = highscore[j];
			highscore[j] = f;

		}
	}
}
void highscores::sort(int elementnum, int elementnum2){
	id f;

	for (int i = 0; i < highscore.size(); i++)
	for (int j = i + 1; j < highscore.size(); j++)
	{
		if (atof(*(highscore[j] + elementnum - 1)) > atof(*(highscore[i] + elementnum - 1)))
		{
			f = highscore[i];
			highscore[i] = highscore[j];
			highscore[j] = f;

		}
		else if (atof(*(highscore[j] + elementnum - 1)) == atof(*(highscore[i] + elementnum - 1)))
		{
			if (atof(*(highscore[j] + elementnum2 - 1)) > atof(*(highscore[i] + elementnum2 - 1)))
			{
				f = highscore[i];
				highscore[i] = highscore[j];
				highscore[j] = f;
			}
		}
	}
}
int highscores::find(string x, int elementnum){

	int v;
		for(int i = 0; i < highscore.size(); i++)
		if (x == *(highscore[i] + elementnum - 1))
		{
			vectorpos = i;
			break;
		}else

		{
			vectorpos = highscore.size();
		}

		return vectorpos;
}
void highscores::copytofile(int elementnum){
	int x = 10;
	ofstream input;
	input.open(filename.c_str);
	sort(elementnum);
	
	if (highscore.size() < x)
	{
		x = highscore.size();
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < numofe; j++)
		{
			input << *(highscore[i] + j)<<'\t';
		}
		input << endl;

	}
	input.close();
}
void highscores::copytofile(int elementnum, int elementnum2){
	int x = 10;
	ofstream input;
	input.open(filename.c_str);
	sort(elementnum, elementnum2);

	if (highscore.size() < x)
	{
		x = highscore.size();
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < numofe; j++)
		{
			input << *(highscore[i] + j) << '\t';
		}
		input << endl;

	}
	input.close();
}
string round(string s)
{	
	string npos = "";
	int found=s.find(.);
	if (found != std::string::npos)
		return s.erase(found + 2);
}
void highscores::file(string name){
	filename="Text.txt";
}
void highscores::sendelements(int a, string b)
{
	*(s + (a - 1)) = b;																																				
}
void highscores::sendelements(int a, int b){
	*(s + (a - 1)) = round(to_string(b));
}
void highscores::sendelements(int a, float b){
	*(s + (a - 1)) = round(to_string(b));
}
void highscores::sendelements(int a, double b){
	*(s + (a - 1)) = round(to_string(b));
}
void highscores::sendelements(int a, char b)
{
	*(s + (a - 1)) = round(to_string(b));
}
void highscores::numofelements(int a)
{
	s = new string[a];
	numofe = a;
}

Text highscores::display(int elementnum)
{
	string t1 = "";
	int x = 10;
	Text t;
	sort(elementnum);
	if (highscore.size() <= x)
	{
		x = highscore.size();
	}
	
	for (int j = 0; j < x; j++)
	{
		t1 += *(highscore[j]+elementnum-1) + "\n";
	}
	
	
	t.setString(t1);
	
	return t;
}