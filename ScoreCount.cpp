#include "ScoreCount.h"
#include <string>
#include <fstream>



ScoreCount::ScoreCount()
{
	_filename = "Highscore.txt" ;
	 ifstream HighscoreFile1("Highscore.txt") ;
	 _currentPoint  = 0 ; 
	 getCurrentHighscore() ;
	 
	//getCurrentHighscore() ;
}

int ScoreCount::incCurrentScore()
{
		_currentPoint++ ;
		
		
		
		_Highschore  ;
	
		if(_currentPoint > _Highschore )
		{
			ofstream newHighscore(_filename);
			newHighscore << _currentPoint ;	
			_Highschore = 	_currentPoint 	;	
		}
		
		
		//cout <<"asdwd      asd " <<_currentPoint  << " " << _Highschore <<endl ;
		return _currentPoint;
		
}

int  ScoreCount::getCurrentHighscore()
{
	
	 
	string line;
	 
	HighscoreFile.open( "Highscore.txt") ; 
	HighscoreFile >> _Highschore  ; 

		
	//cout << "aawesdad sdfsadf asdf "<<_Highschore   <<endl;  
	return _Highschore  ;
	
	
	


}



ScoreCount::~ScoreCount()
{
}

