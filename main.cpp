#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include "Weapon.h"
#include "Player.h"
#include "GUIGyruss.h"
#include "GyrussEnemy.h"
#include "string"

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

 player, sf::Texture &texture,string *path, auto counter) {
		 

if(counter%4 == 0 )	
{
	
	texture.loadFromFile(path[counter%3]);
}

	player.setTexture(texture);
	player.setOrigin(texture.getSize().x*0.5, 0);
	player.setScale(0.2,0.2);
	player.setPosition(250, 450);
=======
sf::Sprite createGameObject(sf::Texture& texture, string TexturePath, sf::Vector2f initPos){
	sf::Sprite sprite;
	texture.loadFromFile(TexturePath);
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x*0.5,texture.getSize().y*0.5));
	sprite.setScale(0.2,0.1);
	sprite.setPosition(initPos.x, initPos.y);
	return sprite;
>>>>>>> b94824d98d34f27a827acf8fadd7a3148db1fae1
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
	GUIGyruss Guigen ;
	

    sf::RenderWindow window(sf::VideoMode(500,500), "Gyruss", sf::Style::Close);
    window.setFramerateLimit(60);
	///Background
	sf::Texture backgroundTexture;
	string backGroundPaths[3] = {"textures/tempBack/1.jpg","textures/tempBack/2.jpg","textures/tempBack/3.jpg"};
	string playerString[3] = { "textures/player.png" , "textures/player1.png","textures/player2.png" } ; 
	
	//Splash screen
	sf::Texture spT1,spT2 , tEnter , tHighscore, tInstructions;
	
	spT1.loadFromFile("textures/tempBack/2.jpg");
	spT2.loadFromFile("textures/tempBack/3.jpg");
	tInstructions.loadFromFile("textures/instructions.png");   
	sf::Sprite background(spT1), instruction(tInstructions)   ;
	background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
	//////Enemy ??????????
	
	//list<GyrussEnemy> a(3); 
	sf::Texture EnemyTexture,EnemyTexture1,EnemyTexture2,EnemyTexture3,EnemyTexture4;
	EnemyTexture.loadFromFile("textures/asteroid.png");
	sf::Sprite EnemySprite, EnemySprite1, EnemySprite2, EnemySprite3, EnemySprite4,DeadEnemySprite ;
	EnemySprite.setTexture(EnemyTexture) ;
	EnemySprite.setOrigin(sf::Vector2f(EnemyTexture.getSize().x*0.5,EnemyTexture.getSize().y*0.5));
	GyrussEnemy testEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	
<<<<<<< HEAD
	sf::Texture logo1 ,logo2 ,logo3  ;
	logo1.loadFromFile("textures/SplashScreen/logo1.png") ;
	 logo2.loadFromFile("textures/SplashScreen/logo2.png") ;
	 logo3.loadFromFile("textures/SplashScreen/logo3.png") ;
	 sf::Sprite slogo1(logo1); 
	 slogo1.setOrigin(-140,-70 ) ;
	
	

=======
	EnemySprite = createGameObject(EnemyTexture,"textures/asteroid.png",sf::Vector2<float> (250,450));
>>>>>>> b94824d98d34f27a827acf8fadd7a3148db1fae1
	GyrussEnemy testEnemyA(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	EnemySprite1 = createGameObject(EnemyTexture1,"textures/generator.png",sf::Vector2<float> (250,450));
	GyrussEnemy testEnemyB(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
	EnemySprite2 = createGameObject(EnemyTexture2,"textures/laser.png",sf::Vector2<float> (250,450));
	GyrussEnemy testEnemyC(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite2, EnemyType::laser);
	EnemySprite3 = createGameObject(EnemyTexture3,"textures/satellites.png",sf::Vector2<float> (250,450));
	EnemySprite3.setScale(0.2,0.2);
	GyrussEnemy testEnemyD(sf::Vector2<float>(0,0), sf::Vector2<float>(250,250), EnemySprite3, EnemyType::satellites, 640);
	GyrussEnemy testEnemyD1(sf::Vector2<float>(0,100), sf::Vector2<float>(250,250), EnemySprite3, EnemyType::satellites, 880);
	GyrussEnemy testEnemyD2(sf::Vector2<float>(0,200), sf::Vector2<float>(250,250), EnemySprite3, EnemyType::satellites, 1020);
	GyrussEnemy testEnemyD3(sf::Vector2<float>(0,300), sf::Vector2<float>(250,250), EnemySprite3, EnemyType::satellites, 1260);
	GyrussEnemy testEnemyD4(sf::Vector2<float>(0,400), sf::Vector2<float>(250,250), EnemySprite3, EnemyType::satellites, 1400);
	EnemySprite4 = createGameObject(EnemyTexture4,"textures/ship.png",sf::Vector2<float> (250,450));
	GyrussEnemy testEnemyE(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite4, EnemyType::ships);
	
	GyrussEnemy testEnemy1(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids);
//	GyrussEnemy enemies[5];
	
	vector<GyrussEnemy> VectorOfEnimies ; 
	
	

	
	//EnemiesManage(VectorOfEnimies, 5);
	GyrussEnemy deadEnemy(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), DeadEnemySprite, EnemyType::asteroids);
	
	
	float timer ; 
	//float timer1 ; 
	////////////////////////////
	sf::Texture playerTexture;
<<<<<<< HEAD
	createPlayer(playerSprite, playerTexture, playerString, countFrames);
    Player mainPlayer(playerSprite, window.getSize(),250,250);
	
=======
	sf::Sprite playerSprite = createGameObject(playerTexture,"textures/player.png", sf::Vector2<float> (250,450));
>>>>>>> b94824d98d34f27a827acf8fadd7a3148db1fae1
	
    Player mainPlayer(playerSprite, window.getSize(),250,250);
	
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
					clock.restart();
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
			Guigen.generateGyrusslogo(countFrames, window );
			instruction.setOrigin(-7,-270);
			window.draw(instruction);

			//window.draw(slogo1) ;
			
			//////
		} else {
			if(countFrames%5 == 0){
				image_number = (++image_number)%3;
				backgroundTexture.loadFromFile(backGroundPaths[image_number]);
				background.setTexture(backgroundTexture);
			}
			window.draw(background);
			testEnemyE.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyD.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyD1.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyD2.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyD3.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyD4.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyC.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyB.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			testEnemyA.updateScreen(window,mainPlayer.getPlayerBullets(), clock.getElapsedTime().asSeconds()) ;
			mainPlayer.update(window,countFrames, 7.0f, testEnemyE.getEnemyBullets());

		
		}
		for(auto j = 0; j < mainPlayer.getPlayerLives(); j++){
			sf::Sprite lives = playerSprite;
			lives.setScale(0.15f,0.1f);
			lives.setPosition(20*j + 30, 460);
			window.draw(lives);
		}
		createPlayer(playerSprite, playerTexture, playerString, countFrames);
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

