#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>

class GUI
{
public:
	GUI();
	void generateGyrusslogo(sf::Clock MainClock, sf::RenderWindow &Mainwindow ) ;
	
	~GUI();

private:
	sf::Texture slogo1 ,slogo2 ,slogo3  ;
	sf::Clock clock ;
	float time , timer ; 
	
 

};

#endif // GUI_H
