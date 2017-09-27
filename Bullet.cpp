#include "Bullet.h"

Bullet::Bullet(float radius, float angle,  string name)
{
	_angle = angle;
	_radius = radius;
	setTag(name);
}

void Bullet::bulletUpdate(const float xRef, const float yRef){
	_xPos = _radius*cos(_angle) + xRef;
	_yPos = _radius*sin(_angle) + yRef;
}

Bullet::~Bullet()
{
}

