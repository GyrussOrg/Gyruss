#ifndef GUIGYRUSS_H
#define GUIGYRUSS_H
#include <SFML/Graphics.hpp>
class GUIGyruss
{
public:
	GUIGyruss();
	void generateGyrusslogo(int cframe, sf::RenderWindow &Mainwindow ) ;
	~GUIGyruss();
private :
	sf::Texture slogo1 ,slogo2 ,slogo3 ,slogo, sEnter  ;
	sf::Clock clock ;
	int counter  ; 
	float time, timer  ;
	

};

#endif // GUIGYRUSS_H
