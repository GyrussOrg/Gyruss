#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include "Weapon.h"
#include "Player.h"
#include "GyrussEnemy.h"
#include "string"
#include  "sstream"

using namespace std;







void EnemiesManage( GyrussEnemy &enemieVector , int NumberOfEnimes)
{
	for(int i = 0  ; i < NumberOfEnimes; i++)
	{
		//GyrussEnemy testEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
		//enemieVector.push_back(testEnemy);
	}
}


void createPlayer(sf::Sprite&

 player, sf::Texture &texture,string path){
	texture.loadFromFile(path);
	player.setTexture(texture);
	player.setOrigin(texture.getSize().x*0.5, 0);
	player.setScale(0.2,0.1);
	player.setPosition(250, 450);
}

int main()
{   
	//////////////////for checking frame rate
    sf::Clock clock;
    sf::Time time;
	auto countFrames = 0;
	bool playGame = false;
	//Weapon weapon;
    /////////////////////////////
	stringstream imagename  ;

	string firstpartofname ="textures/background/Space_Warp_Speed_Effect_Background_HD_0";
	int number = 80 ;
	
	imagename << firstpartofname << number <<".jpg" ; 
	string streamedImageNamed  = imagename.str() ;  

    sf::RenderWindow window(sf::VideoMode(500,500), "Gyruss", sf::Style::Close);
    window.setFramerateLimit(60);
	
	///Background
		sf::Texture backgroundTexture;
		if(backgroundTexture.loadFromFile(streamedImageNamed)){
			cout << "backgrund loaded" << endl;
		}
		
		
		sf::Sprite background(backgroundTexture);
		
		
		
		

		
		
		//background.setPosition(0,0);
		//background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
	//Splash screen
	sf::Texture spT1,spT2;
	spT1.loadFromFile("textures/splash1.png");
	spT2.loadFromFile("textures/splash2.png");
	
	//////Enemy ??????????
	
	//list<GyrussEnemy> a(3); 
	sf::Texture EnemyTexture;
	EnemyTexture.loadFromFile("textures/asteroid.png");
	sf::Sprite EnemySprite, DeadEnemySprite ;
	EnemySprite.setTexture(EnemyTexture) ;
	EnemySprite.setOrigin(sf::Vector2f(EnemyTexture.getSize().x*0.5,EnemyTexture.getSize().y*0.5));
	GyrussEnemy testEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	GyrussEnemy testEnemy1(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	GyrussEnemy enemies[5];
	
	vector<GyrussEnemy> VectorOfEnimies ; 
	


	
	//EnemiesManage(VectorOfEnimies, 5);
	GyrussEnemy deadEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), DeadEnemySprite, EnemyType::asteroids);
	
	
	float timer ; 
	//float timer1 ; 
	////////////////////////////
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	createPlayer(playerSprite, playerTexture,"textures/player.png");
    Player mainPlayer(playerSprite, window.getSize(),250,250);
	
	
	for(int i =0 ; i<5 ; i++ )
	{
		enemies[i].getEnemyID(i+1) ;
		enemies[i].randomAngle(  i+1);
		
	}	
	
	int image_number  =80 ; 
	
    while(window.isOpen()){
		
		imagename.str(std::string()) ;
		window.draw(background);
			float time1 = clock.getElapsedTime().asSeconds() ; 
			//clock.restart() ;
			float time = clock.getElapsedTime().asSeconds() ; 
			clock.restart() ;
			timer +=time ; 
			
			
			

if( image_number < 99)
{				

	if(timer > 0.1 )
		{
		image_number++ ;
		number = image_number ;	
		 imagename << firstpartofname << number <<".jpg" ; 
		 streamedImageNamed  = imagename.str() ;  				
		//cout <<image_number <<endl ; 
		if(backgroundTexture.loadFromFile(streamedImageNamed)){
		}
		
			
			timer = 0 ;
			window.draw(background);
			}
			
			
}else{
	
	image_number = 80 ; 
	}			
		
		
		
        sf::Event event;
        while(window.pollEvent(event)){
			

			
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					playGame = true;
					background.setTexture(backgroundTexture);
					background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
				}
            }
        }
        window.clear();
		
		if(!playGame){
			//Splash screen animation
			if(countFrames < 20){
				background.setTexture(spT1);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
			} else {
				background.setTexture(spT2);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
			
				if(countFrames > 40)
					countFrames = 0;
			}
			window.draw(background);
			//////
		} else {
			window.draw(background);
			for(auto i = 0; i < 5; i++){
				
			//float time = clock.getElapsedTime().asSeconds() ; 
			//clock.restart() ;
			//timer +=time ;
				
				//if (timer > 3 )
				//{
				enemies[i].getEnemyID(i+1) ;

				//timer = 0 ;
				//}
				
				
				enemies[i].updateScreen(window,mainPlayer.getPlayerBullets()) ;
				mainPlayer.update(window,countFrames,enemies[i].getEnemyBullets());
				
					
				if(enemies[i].isEnemyDead()){
					//cout << "enemy " << i ;
					enemies[i].enemySetup(EnemyTexture);
					
				}
			}
			//cout << endl;
		}
		for(auto j = 0; j < mainPlayer.getPlayerLives(); j++){
			sf::Sprite lives = playerSprite;
			lives.setScale(0.15f,0.1f);
			lives.setPosition(20*j + 30, 460);
			window.draw(lives);
		}
        window.display();
		countFrames++;
    }
    return 0;
}

