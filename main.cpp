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
#include  "sstream"
#include "ScoreCount.h"


using namespace std;

float calcAngle(float yDiff, float xDiff);
float lookAt(sf::Sprite& sprite, float angle = 0 ,float xPosition = 250, float yPosition = 250);
void displayScore(sf::RenderWindow& window, ScoreCount& TryHigh, float clock);
sf::Sprite createGameObject(sf::Texture& texture, string TexturePath, sf::Vector2f initPos);
template<typename U>
void spriteModifier(U& object,sf::Sprite& sprite, float scalefactor);

int main()
{   
	
	//////////////////for Gui management
	ScoreCount  TryHigh ;
    sf::Clock clock;
    sf::Time time;
	auto countFrames = 0;
	bool playGame = false;	
	GUIGyruss Guigen ;
    /////////////////////////////
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
	
	 sf::Texture logo1 ,logo2 ,logo3  ;
	 logo1.loadFromFile("textures/SplashScreen/logo1.png") ;
	 logo2.loadFromFile("textures/SplashScreen/logo2.png") ;
	 logo3.loadFromFile("textures/SplashScreen/logo3.png") ;
	 sf::Sprite slogo1(logo1); 
	 slogo1.setOrigin(-140,-70 );	



    sf::RenderWindow window(sf::VideoMode(500,500), "Gyruss", sf::Style::Close);
    window.setFramerateLimit(60);
	auto image_number  = 0; 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////create enemy
	sf::Texture EnemyTexture,EnemyTexture1,EnemyTexture2,EnemyTexture3,EnemyTexture4;
	sf::Sprite  EnemySprite1,EnemySprite2,EnemySprite3,EnemySprite4;
	
	sf::Texture enemyBulletTexture;
	sf::Sprite enemyBulletPrefab = createGameObject(enemyBulletTexture,"textures/enemyBullet.png", sf::Vector2<float> (250,450));
	
	vector<GyrussEnemy> enemies;
	vector<sf::Sprite> EnemySprite;
	EnemySprite1 = createGameObject(EnemyTexture,"textures/ship.png",sf::Vector2<float> (250,450));
	EnemySprite.push_back(EnemySprite1);
	EnemySprite.push_back(EnemySprite1);
	GyrussEnemy ship(250,250,-4*atan(1),EnemyType::ships);
	GyrussEnemy ship2(250,250,0,EnemyType::ships);
	enemies.push_back(ship);
	enemies.push_back(ship2);
	EnemySprite2 = createGameObject(EnemyTexture2,"textures/asteroid.png",sf::Vector2<float> (250,450));
	EnemySprite.push_back(EnemySprite2);
	GyrussEnemy asteroid(250,250,0,EnemyType::asteroids, 1000);
	enemies.push_back(asteroid);
	EnemySprite3 = createGameObject(EnemyTexture3,"textures/satellites.png",sf::Vector2<float> (250,450));
	EnemySprite.push_back(EnemySprite3);
	EnemySprite.push_back(EnemySprite3);
	EnemySprite.push_back(EnemySprite3);
	EnemySprite.push_back(EnemySprite3);
	EnemySprite.push_back(EnemySprite3);
	GyrussEnemy satellite1(250,250,4*atan(1)/2 ,EnemyType::satellites, 1000);
	enemies.push_back(satellite1);
	GyrussEnemy satellite2(250,250,4*atan(1)/2 + 0.125,EnemyType::satellites, 1200);
	enemies.push_back(satellite2);
	GyrussEnemy satellite3(250,250,4*atan(1)/2 + 0.125*2,EnemyType::satellites, 1400);
	enemies.push_back(satellite3);
	GyrussEnemy satellite4(250,250,4*atan(1)/2 + 0.125*3,EnemyType::satellites, 1600);
	enemies.push_back(satellite4);
	GyrussEnemy satellite5(250,250,4*atan(1)/2 + 0.125*4,EnemyType::satellites, 1800);
	enemies.push_back(satellite5);
	GyrussEnemy laser(250,250,4*atan(1)/2 + 0.125*4,EnemyType::laser);
	enemies.push_back(laser);
	EnemySprite4 = createGameObject(EnemyTexture2,"textures/enemyLaser.png",sf::Vector2<float> (250,450));
	EnemySprite.push_back(EnemySprite4);
	//GyrussEnemy 
	
	//SpriteHandler
	
	//SpriteHandler<GyrussEnemy> spriteManager;
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//////create player sprite
	sf::Texture playerTexture;
	sf::Sprite playerSprite = createGameObject(playerTexture,"textures/player.png", sf::Vector2<float> (250,450));
	sf::Texture playerBulletTexture;
	sf::Sprite PlayerBulletPrefab = createGameObject(playerBulletTexture,"textures/laser.png", sf::Vector2<float> (250,450));
    Player mainPlayer(250,250,200);
	
	
	
	vector<GyrussEnemy> temp = enemies;
    while(window.isOpen()){
					
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !playGame){
					playGame = true;
					clock.restart();
					mainPlayer.setPlayerLives(4);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
					window.close();
					break;
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
			displayScore(window, TryHigh, clock.getElapsedTime().asSeconds());
			clock.restart();
			//////
		} else {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					mainPlayer.move(-7.0f);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					mainPlayer.move(7.0f);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (countFrames%3 == 0)){
					mainPlayer.playerShoot();
				}
			if(countFrames%5 == 0){
				image_number = (++image_number)%3;
				backgroundTexture.loadFromFile(backGroundPaths[image_number]);
				background.setTexture(backgroundTexture);
			}
			window.draw(background);
			displayScore(window,TryHigh, clock.getElapsedTime().asSeconds());
			int i = 0;
			for(auto& testEnemyA: temp){
				spriteModifier(testEnemyA,EnemySprite[i],1000);
				testEnemyA.enemyUpdate(mainPlayer.getBullets(),clock.getElapsedTime().asSeconds());
				if(!testEnemyA.isEnemyDead()){
					window.draw(EnemySprite[i]);
				} else {
					if(testEnemyA.getDeadTime() == 600){
						TryHigh.incCurrentScore();
					}
				}
				//draw bullets
				
				for(auto j = 0; j < testEnemyA.getBullets().size();j++){
					Bullet &temp = testEnemyA.getBullets().at(j);
					spriteModifier(temp , enemyBulletPrefab, 2500);
					window.draw(enemyBulletPrefab);
				}
				
				if(i < EnemySprite.size()){
					i++;
				}
			}
			
			
			///////player sequences
			
			if(!mainPlayer.getPlayerLives() == 0){
				for(auto& testEnemyA: temp){
					if(!testEnemyA.isEnemyDead())
					mainPlayer.playerUpdate(testEnemyA.getBullets(),testEnemyA.getCollider(), clock.getElapsedTime().asSeconds());
				}
				playerSprite.setPosition(mainPlayer.getXpos(),mainPlayer.getYpos());
				lookAt(playerSprite, mainPlayer.getAngle());
				
				for(auto i = 0; i < mainPlayer.getBullets().size();i++){
					Bullet& temp = mainPlayer.getBullets().at(i);
					spriteModifier(temp , PlayerBulletPrefab, 1500);
					window.draw(PlayerBulletPrefab);
				}
				//update colliders
				mainPlayer.colliderUpdate(playerSprite.getGlobalBounds());
				for(auto j = 0; j < mainPlayer.getPlayerLives(); j++){
					sf::Sprite lives = playerSprite;
					lives.setScale(0.15f,0.1f);
					lives.setPosition(20*j + 30, 460);
					window.draw(lives);
				}
				window.draw(playerSprite);
			} else {
				countFrames = 0;
					sf::Texture gameOverTexture ;
					gameOverTexture.loadFromFile("textures/gameOver.png");
					sf::Sprite gameOver = createGameObject(gameOverTexture, "textures/gameOver.png", sf::Vector2<float> (250,250));
					gameOver.setScale(1,1);
				while(1){
					countFrames++;
					window.draw(gameOver);
					window.display();
					if(countFrames > 100){
						temp.clear();
						temp = enemies;
						TryHigh.reset();
						playGame = false;
						break;
					}
				}
			}
			
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

template<typename U>
void spriteModifier(U& gameObject,sf::Sprite& sprite, float scalefactor){
	sprite.setPosition(gameObject.getXpos(),gameObject.getYpos());
	sprite.setScale(gameObject.getRadius()/(scalefactor/1.5), gameObject.getRadius()/scalefactor);
	lookAt(sprite,gameObject.getAngle());
	gameObject.colliderUpdate(sprite.getGlobalBounds());
}

float calcAngle(float yDiff, float xDiff){
	
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

float lookAt(sf::Sprite& sprite, float angle,float xPosition, float yPosition){
	float tempAngle;
	if(!(xPosition == 250 && yPosition == 250)){
		auto tempX = sprite.getPosition().x;
		auto tempY = sprite.getPosition().y;
		tempAngle = calcAngle(yPosition - tempY ,  tempX - xPosition);
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	} else {
		tempAngle = angle;
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	}
	return tempAngle*180/(4*atan(1));
} 

void displayScore(sf::RenderWindow& window, ScoreCount& TryHigh, float clock){
	sf::Font font;
	font.loadFromFile("Tr2n.ttf"); 
	sf::Text text , text1 ;
	text.setFont(font);
	text.setCharacterSize(11); 
	text.setColor(sf::Color::Cyan);
	text.setStyle(sf::Text::Bold );

	text1.setFont(font);
	text1.setCharacterSize(11); 
	text1.setColor(sf::Color::White);
	text1.setStyle(sf::Text::Bold );
	
	stringstream displayscore ;
	auto score = TryHigh.getCurrentScore();
	displayscore  <<"Current Score " << score ;
	string sdisplayscore = displayscore.str();
	
	stringstream displayHighscore ;
	displayHighscore  <<"Highscore " << TryHigh.getCurrentHighscore();
	
	string sdisplayHighscore = displayHighscore.str();
	
	text.setString(sdisplayscore );
	text.setPosition(340,470) ;
	window.draw(text); 
	
	text1.setString(sdisplayHighscore );
	text1.setPosition(340,480) ;
	window.draw(text1); 
	
	text.setFont(font);
	text.setCharacterSize(18); 
	text.setColor(sf::Color::Cyan);
	text.setStyle(sf::Text::Bold );
	text.setString("Press escape to exit");
	text.setPosition(115,20) ;
	if(clock < 2.0f)
	window.draw(text); 
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