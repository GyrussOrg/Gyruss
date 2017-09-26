#ifndef PLAYER_H
#define PLAYER_H
#include  <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <deque>
#include <string>
#include "Weapon.h"
#include "Collider.h"
#include <iostream>


using namespace std;

class Player:public Weapon
{
public:
	Player(float refX,float refY, float radius);
	float getAngle(){return _angle;}
	float getRadius(){return _radius;}
	float getX(){return _xPos;}
	float getY(){return _yPos;}
	void shoot(){ playerShoot(_radius,_angle,"playerBullet");}
	void move(float speed);
	int getPlayerLives(){return _lives;}
	deque<Bullet>& getPlayerBullets(){return getBullets();}
	void update(sf::RenderWindow& window, deque<Bullet>& enemyBullets);
	~Player();
private:
	float _radius;
	float _angle;
	float _refX;
	float _refY;
	float _xPos;
	float _yPos;
	int _lives;
};

#endif // PLAYER_H
