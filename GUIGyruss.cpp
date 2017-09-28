#include "GUIGyruss.h"
#include "iostream"
using namespace std ;

GUIGyruss::GUIGyruss()
{
	 
	 counter = 0;
	 
}

void GUIGyruss::generateGyrusslogo(int cframe, sf::RenderWindow &Mainwindow ) 
{
	
	string logoPath[6]  = {"textures/SplashScreen/logo1.png","textures/SplashScreen/logo2.png","textures/SplashScreen/logo3.png",
"textures/SplashScreen/logo4.png","textures/SplashScreen/logo5.png","textures/SplashScreen/logo6.png"};
	string EnterPath[6] = {"textures/SplashScreen/enter1.png"  , "textures/SplashScreen/enter2.png" ,"textures/SplashScreen/enter3.png" ,
	"textures/SplashScreen/enter4.png" ,"textures/SplashScreen/enter5.png" ,"textures/SplashScreen/enter6.png" } ;
	
	 time = clock.getElapsedTime().asSeconds() ; 		
	
	
	timer +=time ;
	
	if(counter > 3)
	{
	
		counter = 0 ;
		
	}
	
	if( timer > 0.5 )
	{
			
		counter++ ;
		slogo.loadFromFile(logoPath[counter]) ; 
		sEnter.loadFromFile(EnterPath[counter] ) ;	
		timer = 0 ;
		clock.restart() ;
		
		
	} 
	
	
	
	sf::Sprite  logo(slogo) ; 
	sf::Sprite  Enter(sEnter);
	logo.setOrigin(-141,-70);
	Enter.setOrigin(-30,-190) ;
	Mainwindow.draw(logo) ; 
	Mainwindow.draw(Enter) ;
	
	

	/*	
		if (cframe%9 == 0)
		{
			Mainwindow.draw(logo1) ; 
			cout <<timer << endl;
		
		}else
		{
			Mainwindow.draw(logo2) ; 
			
			if(cframe%5 == 0 )
			{
				timer = 0 ; 
				cout <<timer << endl;
			}
		}


	*/
	
	
	
	
}
GUIGyruss::~GUIGyruss()
{
}

