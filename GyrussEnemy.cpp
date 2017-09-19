#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		_isDead = false;
		_radius = 0.1f;
		if(EnemyTexture.loadFromFile("textures/enemy.png") ){
			cout << "enemy sprite loaded" << endl;
		}
		length = 500; 
		width = 500; 
		EnemySprite.setTexture(EnemyTexture) ; 
		int ts = 1 ;
		_x = 250; 
		_y=  250;
		
		_xRefPoint = ((width-1)/2)*ts;
		_yRefPoint = ((length -1)/2)*ts; 
		_dx = 4 - rand()%8 ; 
		_dy = 4 - rand()%8 ; 
		
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		_enemyCollider.setTag("enemyCollider");
	
}


void GyrussEnemy::move()
{
	_radius = 100;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	// int changeinX = (_xRefPoint - _x)  ,changeinY = (_yRefPoint -  _y) ;
		//EnemySprite.rotate(200) ;
		_dTheta += 0.05f;
}

float randomAngle(){
	srand(time(0));
	return 8*atan(1)/(rand()%13 + 1);
}
void GyrussEnemy::moveOutwards(){
	_radius += 0.6f;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint; 
	
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(_radius/100, _radius/200);
	if(_radius  > 500){
		_dTheta *= -1*randomAngle(); 
		_radius = 0;
	}
}

float tempTime = 0;
void GyrussEnemy::updateScreen( sf::RenderWindow &window, vector<Collider> playerBullets)
{	
	float timeE = clockE.getElapsedTime().asSeconds ();
	///this is were the enemy chooses the move
	moveOutwards() ; 
	////////////////////
	float xDiff = _x - _xRefPoint;
	float yDiff = _yRefPoint - _y;
	tempTime += timeE;
	if(tempTime > 0.1){
		//cout << " enemy shooting" << endl;
		//_enemyWeapon.enemyShoot(*this, "enemyBullet");
		tempTime = 0;
	}
	timeE = clockE.restart().asSeconds();
	//_enemyWeapon.weaponUpdate(window,sf::Vector2<float> (250,250), 1.0f);
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	int i = 0;
	if(_enemyCollider.collided(playerBullets,i) && !playerBullets.empty()){
		if(playerBullets.at(i - 1).getTag() == "playerBullet"){
			_isDead = true;
			
		}
	}
	//std::cout <<"x: " << _x << "y: " << _y << std::endl ; ,
	window.draw(EnemySprite) ;
}


void GyrussEnemy::updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets){
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	
	moveOutwards() ; 

	auto i = 0;
	for(auto& bullet:playerBullets){
		if(_enemyCollider.collided(bullet.bulletCollider)){
			if(bullet.bulletCollider.isCollided()){
				continue;
			}
			bullet.bulletCollider.setCollisionStatus(true);
			if(bullet.bulletCollider.getTag() == "playerBullet"){
				_isDead = true;
			}
		}
	}
	window.draw(EnemySprite);
}



void GyrussEnemy::enemySetup(sf::Texture texture,sf::Vector2f initialPosition, sf::Vector2f scale){
	EnemyTexture = texture;
	EnemySprite.setPosition(initialPosition);
	EnemySprite.setScale(scale);
}

GyrussEnemy::GyrussEnemy( sf::Vector2f initPos, sf::Vector2f refPoint ,sf::Sprite& enemyObject, EnemyType enemyType = EnemyType::ships)
:_x{initPos.x} , _y{initPos.y}, _xRefPoint{refPoint.x}, _yRefPoint{refPoint.y} , EnemySprite{enemyObject}, _enemyType{enemyType}
{
	if(enemyType == EnemyType::asteroids){
		_dTheta = randomAngle();
		_radius = 0;
	}
}


/*
switch(enemyType){
		case EnemyType::ships:
			break;
		case EnemyType::satellites:
			break;
		case EnemyType::laser:
			break;
		case EnemyType::generator:
			break;
		case EnemyType::asteroids:
			break;
		default:
			break;
	} 
	*/