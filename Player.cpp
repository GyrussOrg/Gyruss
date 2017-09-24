#include "Player.h"
#include "Weapon.h"

Player::Player(sf::Sprite& sprite,sf::Vector2u screenSize, float refX, float refY)
:_radius{200.0f}, _angle{PI/2}, _refX{refX}, _refY{refY}, _xPos{250}, _yPos{450}, _lives{4}, _playerSprite{sprite}
{		
		_playerCollider.update(_playerSprite.getGlobalBounds());
		_playerCollider.setTag("playerCollider");
}


Player::~Player()
{
}

void  Player::moveLeft(float time){
		_angle += PI*time/600;
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);	
}
void Player::moveRight(float time){
	_angle -= PI*time/600;
	_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
	_playerSprite.setRotation(_angle*180/PI - 90);
	
}

void Player::update(sf::RenderWindow& window, int countFrames, float time ,deque<Bullet>& enemyBullets){
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		moveRight(time);
		//cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		moveLeft(time);
		//cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (countFrames%7 == 0)){
			_gun.playerShoot(*this,"playerBullet");
			countFrames = 0;
	}
	sf::Vector2f ref(_refX,_refY) ;
	_gun.weaponUpdate(window, ref, -1.0f);
	_playerCollider.update(_playerSprite.getGlobalBounds());
	auto i = 0;
	for(auto& bullet:enemyBullets){
		if(_playerCollider.collided(bullet.bulletCollider) && _lives > 0){
			if(bullet.bulletCollider.isCollided()){
				continue;
			}
			cout << "Collided with " << bullet.bulletCollider.getTag() << " lives " << _lives << endl;
			bullet.bulletCollider.setCollisionStatus(true);
			_lives -=1;
		}
	}
	if(_lives > 0){
		_playerCollider.setCollisionStatus(false);
	}
	window.draw(_playerSprite);
	//clockP.restart();
}
/*
virtual float Player::getAngle(){
	float xDiff = _xPos - _xRef;
	float yDiff = _yRef - _yPos;
	
	float angle = atan(yDiff/(xDiff+ 0.00001f))
	
	if(yDiff >= 0 && xDiff >= 0){ //first quadrant
		angle -= 4*atan(1)/2;
	} else if (yDiff >= 0 && xDiff < 0){ //second quadrant
		angle -= 4*atan(1)/2;
	} else if (yDiff < 0 && xDiff < 0){ //third quadrant
		angle += 4*atan(1)/2;
	}else if (yDiff < 0 && xDiff >= 0){ //fourth quadrant
		angle += 4*atan(1)/2;
	}
	
	return _angle;
}
*/