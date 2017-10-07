#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include <cmath>
#include "Collider.h"

using namespace std;

class Bullet: public Collider
{
public:
	Bullet(float radius, float angle, string name = "bullet");
	void moveBullet(float speed){ _radius += speed;}
	void bulletUpdate(const float xRef, const float yRef);
	float getXpos(){return _xPos;}
	float getYpos(){return _yPos;}
	float getRadius(){return _radius;}
	float getAngle(){return _angle;}
	~Bullet();
	
private:
	float _xPos;
	float _yPos;
	float _angle;
	float _radius;

};

#endif // BULLET_H

