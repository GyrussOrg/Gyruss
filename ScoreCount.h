#ifndef SCORECOUNT_H
#define SCORECOUNT_H
#include<fstream>
#include <iostream>

using namespace std; 

class ScoreCount
{
public:
	ScoreCount();
	int getCurrentHighscore() ; 
	int incCurrentScore() ;
	int getCurrentScore(){return _currentPoint;}
	void reset(){ _currentPoint = 0;}
	
	~ScoreCount();
private:
	 int _Highschore ;
	ifstream HighscoreFile;
	string _filename  ;
	int _currentPoint ;
	
};

#endif // SCORECOUNT_H
