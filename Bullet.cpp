#include "Bullet.h"

Bullet::Bullet(float radius, float angle,  string name)
{
	_angle = angle;
	_radius = radius;
	//setTag(name);
}

void Bullet::bulletUpdate(sf::Vector2f refPoint, sf::Sprite& bullet){
	_xPos = _radius*cos(_angle) + refPoint.x;
	_yPos = _radius*sin(_angle) + refPoint.y;
	bullet.setPosition(_xPos,_yPos);
	//colliderUpdate(bullet.getGlobalBounds());
}

Bullet::~Bullet()
{
}

