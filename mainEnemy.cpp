#include <SFML/Graphics.hpp>
#include "GyrussEnemy.h"
#include "iostream"


using namespace std ; 
using namespace sf ; 

int main()
{
	
	srand(time(0)) ; 
	const int width  = 500 , length = 500;
    sf::RenderWindow window(sf::VideoMode(width, length ), "Gyruss");
	window.setFramerateLimit(60);
	
	Texture EnemyTexture ; 
	EnemyTexture.loadFromFile("textures/Space_Warp_Speed_Effect_Background_HD_000.png" );
	Sprite sEnemy(EnemyTexture) ;  
	
	sEnemy.setOrigin(20,20) ; 
	int enemyCount = 10 ; 
	GyrussEnemy a[10] ; 
	
	
	int x = 0 , y = 0 ,dx = 0 , dy = 0 ; 
	float timer=0 , delay = 0.07 ;
	Clock clock ; 
   
    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds() ; 
		clock.restart() ;
		timer +=time ;		
		Event event  ; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		/*
		for(int i= 0 ; i < enemyCount; i++) 
			{
				a[i].move() ; 		
				cout <<"x: " << a[i].getX() << "y: " << a[i].getY() <<endl ; ; 
			
			}
		*/
		
		window.clear() ; 

	


    
        window.display();
    }

    return 0;
}