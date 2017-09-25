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

    sf::RenderWindow window(sf::VideoMode(500,500), "Gyruss", sf::Style::Close);
    window.setFramerateLimit(60);
	
	///Background
	sf::Texture backgroundTexture;
	string backGroundPaths[3] = {"textures/tempBack/1.jpg","textures/tempBack/2.jpg","textures/tempBack/3.jpg"};
	
	//Splash screen
	sf::Texture spT1,spT2;
	spT1.loadFromFile("textures/tempBack/2.jpg");
	spT2.loadFromFile("textures/tempBack/3.jpg");
	sf::Sprite background(spT1);
	background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
	//////Enemy ??????????
	
	//list<GyrussEnemy> a(3); 
	sf::Texture EnemyTexture,EnemyTexture1,EnemyTexture2;
	EnemyTexture.loadFromFile("textures/asteroid.png");
	sf::Sprite EnemySprite, EnemySprite1, EnemySprite2,DeadEnemySprite ;
	EnemySprite.setTexture(EnemyTexture) ;
	EnemySprite.setOrigin(sf::Vector2f(EnemyTexture.getSize().x*0.5,EnemyTexture.getSize().y*0.5));
	GyrussEnemy testEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	
	GyrussEnemy testEnemyA(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	EnemyTexture1.loadFromFile("textures/generator.png");
	EnemySprite1.setTexture(EnemyTexture1);
	EnemySprite1.setScale(0.1,0.1);
	EnemySprite1.setOrigin(sf::Vector2f(EnemyTexture1.getSize().x*0.5,EnemyTexture1.getSize().y*0.5));
	GyrussEnemy testEnemyB(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator) ;
	EnemyTexture2.loadFromFile("textures/laser.png");
	EnemySprite2.setTexture(EnemyTexture2);
	EnemySprite2.setScale(0.1,0.1);
	EnemySprite2.setOrigin(sf::Vector2f(EnemyTexture2.getSize().x*0.5,EnemyTexture2.getSize().y*0.5));
	GyrussEnemy testEnemyC(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite2, EnemyType::laser) ;
	GyrussEnemy testEnemyD(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::satellites) ;
	GyrussEnemy testEnemyE(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::ships) ;
	
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
					
        sf::Event event;
        while(window.pollEvent(event)){
			

			
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					playGame = true;
				}
            }
        }
        window.clear();
		
		if(!playGame){
			//Splash screen animation
			if(countFrames < 20){
				background.setTexture(spT1);
			} else {
				background.setTexture(spT2);
			
				if(countFrames > 40)
					countFrames = 0;
			}
			window.draw(background);
			//////
		} else {
			if(countFrames%5 == 0){
				image_number = (++image_number)%3;
				backgroundTexture.loadFromFile(backGroundPaths[image_number]);
				background.setTexture(backgroundTexture);
			}
			window.draw(background);
			//for(auto i = 0; i < 5; i++){
				testEnemyC.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
				mainPlayer.update(window,countFrames, 5.0f, testEnemyC.getEnemyBullets());

			//}
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
		if(countFrames > 60 ){
			countFrames = 0;
		}
		if(clock.getElapsedTime().asSeconds() > 60.0f){
				clock.restart();
		}
    }
    return 0;
}

