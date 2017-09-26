#include "Player.h"

Player::Player(float refX, float refY, float radius){
		_refX = refX;
		_refY = refY;
		_radius = radius;
		_angle = 4*atan(1)/2;
		_xPos = 250;
		_yPos = 450;
		_lives = 4;
		//setTag("playerCollider");
}


Player::~Player()
{
}

void  Player::move(float speed){
		_angle += 4*atan(1)*speed/600;
		_xPos =  _refX + _radius*cos(_angle);
		_yPos = _refY + _radius*sin(_angle);
}

void Player::update(sf::RenderWindow& window,deque<Bullet>& enemyBullets){
	 
	sf::Vector2f ref(_refX,_refY) ;
	weaponUpdate(window, ref, -1.0f);
	for(auto& bullet:enemyBullets){
		/*
		if(collided(bullet.bulletCollider) && _lives > 0){
			if(bullet.bulletCollider.isCollided()){
				continue;
			}
			cout << "Collided with " << bullet.bulletCollider.getTag() << " lives " << _lives << endl;
			bullet.bulletCollider.setCollisionStatus(true);
			_lives -=1;
		}*/
	}
	if(_lives > 0){
		//setCollisionStatus(false);
	}
}