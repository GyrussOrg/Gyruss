#include "GyrussEnemy.h"
float calcAngle(float yDiff, float xDiff){
	
	float angle = atan(yDiff/(xDiff+ 0.00001f));
	if(yDiff >= 0 && xDiff >= 0){ //first quadrant
	} else if (yDiff >= 0 && xDiff < 0){ //second quadrant
		angle += 4*atan(1);
	} else if (yDiff < 0 && xDiff < 0){ //third quadrant
		angle += 4*atan(1);
	}else if (yDiff < 0 && xDiff >= 0){ //fourth quadrant
		angle *=-1 ;
	}
	return angle;
}


float lookAt(sf::Sprite& sprite, float angle = 0 ,float xPosition = 250, float yPosition = 250){
	float tempAngle;
	if(!(xPosition == 250 && yPosition == 250)){
		auto tempX = sprite.getPosition().x;
		auto tempY = sprite.getPosition().y;
		tempAngle = calcAngle(yPosition - tempY ,  tempX - xPosition);
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	} else {
		tempAngle = angle;
		sprite.setRotation(tempAngle*180/(4*atan(1)) - 90);
	}
	return tempAngle*180/(4*atan(1));
} 
 float randomAngle(){
	srand(time(0));
	int temp1 = (rand()%8 + 1);
	float Temp =  8.0*atan(1.0)/float(temp1) ;
	
	return  Temp;
}


void GyrussEnemy::moveCircular(float scaleFactor, float radius)
{
	_radius = radius;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
		_dTheta += 0.01f;
}

void GyrussEnemy::moveOutwards(float scaleFactor, float speed){
	_radius += speed;
	_dTheta = _dTheta ;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint; 
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
	if(_radius  > 1000){
		_dTheta += -1*randomAngle();
		lookAt(EnemySprite,_dTheta); 
		_radius = 0;
		frames = 0;
	}
}

void GyrussEnemy::updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets, float clock){
	if(!_isDead){
		
		switch(_enemyType){
			case EnemyType::ships:
				if(clock > 5.0f ){
					converging(600,9.0f,clock);
				} else{
					lemniscate(1000, 20.0f);
				}
				lookAt(EnemySprite,_dTheta);
				break;
			case EnemyType::satellites:
				if( frames > 1500){
					converging(1500,9.0,clock);
				} else{
					frames++;
					ArchimedesSpiral(1500, 10.0f);
				}
				break;
			case EnemyType::laser:
				moveOutwards(1000, 5.0f);
				break;
			case EnemyType::generator:
				if(_dTheta > 6.28f){
					converging(1000, 9.0f, clock);
					EnemySprite.rotate(10);
				} else{
					Limacons(1000);
					EnemySprite.rotate(2);
				}
				break;
			case EnemyType::asteroids:
				moveOutwards(2000, 1.0f);
				break;
			default:
				break;
		}
		
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		
		if(_enemyType == EnemyType::ships){
			
			if(frames%(rand()%500+1) == 1){
				_enemyWeapon.enemyShoot(*this, "enemyBullet");
			}
			_enemyWeapon.weaponUpdate(window,sf::Vector2<float> (250,250), 1.0f);
		}
		_enemyCollider.update(EnemySprite.getGlobalBounds());
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
	
	}
	window.draw(EnemySprite);
}


GyrussEnemy::GyrussEnemy( sf::Vector2f initPos, sf::Vector2f refPoint ,sf::Sprite& enemyObject, EnemyType enemyType = EnemyType::ships)
:_x{initPos.x} , _y{initPos.y}, _xRefPoint{refPoint.x}, _yRefPoint{refPoint.y} , EnemySprite{enemyObject}, _enemyType{enemyType}
{
		frames = 0;
		_centreRadius   = 15 ; 
		_xscale = EnemySprite.getScale().x ;
		_yscale = EnemySprite.getScale().y ;

	switch(enemyType){
		case EnemyType::ships:
			_dTheta = randomAngle();
			_enemyCollider.setTag("ship");
			break;
		case EnemyType::satellites:
			_dTheta = calcAngle(refPoint.y - initPos.y, initPos.x - refPoint.x);
			_radius = abs(initPos.x - refPoint.x)/(cos(_dTheta) + 0.00001f);
			_enemyCollider.setTag("satellite");
			break;
		case EnemyType::laser:
			_dTheta = randomAngle();
			lookAt(EnemySprite,_dTheta);
			_enemyCollider.setTag("laser");
			break;
		case EnemyType::generator:
			_dTheta = randomAngle();
			_enemyCollider.setTag("generator");
			break;
		case EnemyType::asteroids:
			_dTheta = randomAngle();
			_radius = 0;
			_enemyCollider.setTag("asteroid");
			break;
		default:
			break;
	} 
	
}

void GyrussEnemy::converging(float scaleFactor, float convergingRad, float clock) 
{
	
	if(_radius > convergingRad && frames < 600){
		moveOutwards(scaleFactor, -1.0f);
	}else{
		if(frames < 600){
			frames++;
			moveCircular(scaleFactor, convergingRad);
		} else {
			moveOutwards(scaleFactor, 1.0f);
		}
	}
}


void GyrussEnemy::lemniscate(float scaleFactor, float speed) {
	_dTheta  += (0.0005 * speed);
	int a = 200;
	double TempCos =    fabs(cos(1 *_dTheta)) ;
	_x =  cos(_dTheta)*sqrt( pow(a,2) *TempCos)    +_xRefPoint  ;
	_y = sin(_dTheta)*sqrt( pow(a,2) *TempCos )   +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	_radius = sqrt(  pow(  cos(_dTheta)*sqrt( pow(a,2) * TempCos)   ,2) + pow( sin(_dTheta)*sqrt( pow(a,2)*TempCos ),2)); 
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
}

void GyrussEnemy::ArchimedesSpiral(float scaleFactor, float speed) 
{
	
	_dTheta  += 0.0005*speed    ;
	_radius =  500 / abs(_dTheta)   ;
	
	if(_radius >= 0 )
	{
		_x = _radius*cos(_dTheta) + _xRefPoint  ; 
		_y = _radius*sin(_dTheta) +    _yRefPoint;
		EnemySprite.setPosition(_x, _y ) ;
		EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);	
	}
	
}


void GyrussEnemy::Limacons(float scaleFactor) {
	int a = 40 , b = 80 ;  
	_dTheta +=0.005f ; 
	_x = (a + b*sin(_dTheta))*cos(_dTheta)+_xRefPoint ;
	_y = (a + b*sin(_dTheta))*sin(_dTheta)+ _yRefPoint;
	_radius = sqrt((_x - _xRefPoint)*(_x - _xRefPoint) + (_y - _yRefPoint)*(_y - _yRefPoint));
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
}
