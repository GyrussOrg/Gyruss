#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace std;

class Bullet
{
public:
	Bullet(float radius, float angle, string name = "bullet");
	void moveBullet(float speed){ _radius += speed;}
	void bulletUpdate(sf::Vector2f refPoint,  sf::Sprite& bullet);
	~Bullet();
	
private:
	float _xPos;
	float _yPos;
	float _angle;
	float _radius;

};

#endif // BULLET_H

