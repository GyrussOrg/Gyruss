#ifndef PLAYER_H
#define PLAYER_H
#include  <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <deque>
#include <string>
#include "Weapon.h"
#include "Collider.h"
#include <iostream>


using namespace std;

class Player
{
public:
	sf::Clock clockP;
	const float PI = 4*atan(1);
	Player(){}
	Player(sf::Sprite& sprite,sf::Vector2u screenSize,float refX,float refY);
	sf::Vector2f getPlayerPosition(){return _playerSprite.getPosition();}
	float getPlayerRotation(){return _playerSprite.getRotation();}
	float getAngle(){return _angle;}
	float getRadius(){return _radius;}
	void moveLeft(float time);
	void moveRight(float time);
	int getPlayerLives(){return _lives;}
	deque<Bullet>& getPlayerBullets(){return _gun.getBullets();}
	void update(sf::RenderWindow& window,int countFrames, float time ,deque<Bullet>& enemyBullets);
	~Player();
private:
	float _radius;
	float _angle;
	float _refX;
	float _refY;
	float _xPos;
	float _yPos;
	int _lives;
	sf::Sprite _playerSprite;
	Weapon _gun;
	Collider _playerCollider;
};

#endif // PLAYER_H
