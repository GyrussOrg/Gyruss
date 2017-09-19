#include "Player.h"
#include "Weapon.h"

Player::Player(sf::Vector2u screenSize, float refX, float refY)
:_radius{200.0f}, _angle{PI/2}, _refX{refX}, _refY{refY}
{
		_playerTexture.loadFromFile("textures/player.png");
		_playerSprite.setTexture(_playerTexture);
		float scaleFactor = 10;
		_playerSprite.setScale(500/(scaleFactor * (float)_playerSprite.getTextureRect().width),
								500/(scaleFactor*(float)_playerSprite.getTextureRect().height));
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
		_playerSprite.setOrigin(_playerTexture.getSize().x*0.4, _playerTexture.getSize().y*0);
		
		_playerCollider.update(_playerSprite.getGlobalBounds());
		_playerCollider.setTag("playerCollider");
}


Player::~Player()
{
	//cout << "player deleted" << endl;
}

void Player::update(sf::RenderWindow& window, int& countFrames, vector<Collider> enemyBullets){
	sf::Time timeP = clockP.getElapsedTime();
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		_angle -= PI*timeP.asMilliseconds()/600;
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
		//cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		_angle += PI*timeP.asMilliseconds()/600;
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
		//cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && countFrames > 15){
			//cout << "shoot" << endl;
			_gun.playerShoot(*this,"playerBullet");
			countFrames = 0;
	}
	sf::Vector2f ref(_refX,_refY) ;
	_gun.weaponUpdate(window, ref, -1.0f);
	_playerCollider.update(_playerSprite.getGlobalBounds());
	auto i = 0;
	//enemyBullets = _gun.getBulletCollider();
	if(_playerCollider.collided(enemyBullets,i) && !enemyBullets.empty()){
		//cout << "Collided with " << enemyBullets.at(i - 1).getTag() << endl;
	}
	window.draw(_playerSprite);
	timeP = clockP.restart();
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