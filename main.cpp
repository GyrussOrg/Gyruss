#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include "Weapon.h"
#include "Player.h"
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
float calcAngle2(float yDiff, float xDiff){
	
	float angle = atan(yDiff/(xDiff+ 0.00001f));
	if(yDiff >= 0 && xDiff >= 0){ //first quadrant
		angle *=-1 ;
	} else if (yDiff >= 0 && xDiff < 0){ //second quadrant
		angle = 4*atan(1) - angle;
	} else if (yDiff < 0 && xDiff < 0){ //third quadrant
		angle = 4*atan(1) - angle;
	}else if (yDiff < 0 && xDiff >= 0){ //fourth quadrant
		angle *=-1 ;
	}
	return angle;
}


float lookAt2(sf::Sprite& sprite, float angle = 0 ,float xPosition = 250, float yPosition = 250){
	float tempAngle;
	if(!(xPosition == 250 && yPosition == 250)){
		auto tempX = sprite.getPosition().x;
		auto tempY = sprite.getPosition().y;
		tempAngle = calcAngle2(yPosition - tempY ,  tempX - xPosition);
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	} else {
		tempAngle = angle;
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	}
	cout << sprite.getRotation() << " --- rotation" << endl;
	return tempAngle*180/(4*atan(1));
} 


sf::Sprite createGameObject(sf::Texture& texture, string TexturePath, sf::Vector2f initPos){
	sf::Sprite sprite;
	texture.loadFromFile(TexturePath);
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x*0.5,texture.getSize().y*0.5));
	sprite.setScale(0.2,0.1);
	sprite.setPosition(initPos.x, initPos.y);
	return sprite;
}


int main()
{   
	//////////////////for checking frame rate
    sf::Clock clock;
    sf::Time time;
	auto countFrames = 0;
	bool playGame = false;
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
	//////Enemy ??????????
	
	//list<GyrussEnemy> a(3); 
	sf::Texture EnemyTexture,EnemyTexture1,EnemyTexture2,EnemyTexture3,EnemyTexture4;
	sf::Sprite EnemySprite, EnemySprite1,EnemySprite2,EnemySprite3,EnemySprite4;
	
	EnemySprite = createGameObject(EnemyTexture,"textures/asteroid.png",sf::Vector2<float> (250,450));
	GyrussEnemy testEnemyA(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite, EnemyType::asteroids) ;
	EnemySprite1 = createGameObject(EnemyTexture1,"textures/generator.png",sf::Vector2<float> (250,450));
	GyrussEnemy testEnemyB(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
	GyrussEnemy testEnemyB1(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
	GyrussEnemy testEnemyB2(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
	GyrussEnemy testEnemyB3(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
	GyrussEnemy testEnemyB4(sf::Vector2<float>(250,250), sf::Vector2<float>(250,250), EnemySprite1, EnemyType::generator);
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
	
	float timer ; 
	////////////////////////////
	sf::Texture playerTexture;
	sf::Sprite playerSprite = createGameObject(playerTexture,"textures/player.png", sf::Vector2<float> (250,450));
	
    Player mainPlayer(250,250,200);
	
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
			//for player
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				mainPlayer.move(-7.0f);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				mainPlayer.move(7.0f);
			}
			playerSprite.setPosition(mainPlayer.getX(),mainPlayer.getY());
			lookAt2(playerSprite, mainPlayer.getAngle());
			mainPlayer.colliderUpdate(playerSprite.getGlobalBounds());
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (countFrames%7 == 0)){
				mainPlayer.shoot();
			}
			mainPlayer.update(testEnemyE.getEnemyBullets());

		
		}
		for(auto j = 0; j < mainPlayer.getPlayerLives(); j++){
			sf::Sprite lives = playerSprite;
			lives.setScale(0.15f,0.1f);
			lives.setPosition(20*j + 30, 460);
			window.draw(lives);
		}
		window.draw(playerSprite);
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

