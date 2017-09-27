#include "Player.h"

Player::Player(float refX, float refY, float radius){
		_refX = refX;
		_refY = refY;
		_radius = radius;
		_angle = 4*atan(1)/2;
		_xPos = 250;
		_yPos = 450;
		_lives = 4;
		setTag("playerCollider");
}


Player::~Player()
{
}

void  Player::move(float speed){
		_angle += 4*atan(1)*speed/600;
		_xPos =  _refX + _radius*cos(_angle);
		_yPos = _refY + _radius*sin(_angle);
}

void Player::playerUpdate( deque<Bullet>& enemyBullets, Collider& enemy){
	weaponUpdate(-1.0f);
	if(collided(enemy)){
		_lives -= 1;
		move(600);
	}
	for(auto& bullet:enemyBullets){
		if(collided(bullet.getCollider()) && _lives > 0){
			if(bullet.isCollided()){
				enemyBullets.pop_front();
				continue;
			}
			move(600);
			//cout << "Collided with " << bullet.getTag() << " lives " << _lives << endl;
			bullet.setCollisionStatus(true);
			_lives -=1;
		}
	}
	if(_lives > 0){
		setCollisionStatus(false);
	}
}