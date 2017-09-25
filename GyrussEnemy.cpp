#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		_isDead = false;
		_radius = 0.1f;
		if(EnemyTexture.loadFromFile("textures/asteroid.png") ){
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
		//allEnemies.push_back(*this);
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

 float GyrussEnemy::randomAngle(int EnemyID){
	srand(time(0));
	int temp1 = (rand()%13 + 1);
	float Temp =  8.0*atan(1.0)/float(temp1) ;
	
	return  Temp* EnemyID ;
}
void GyrussEnemy::moveOutwards(float scaleFactor, float speed){
	_radius += speed;
	_dTheta = _dTheta ;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint; 
	
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
	if(_radius  > 500){
		_dTheta += -1*randomAngle(_EnemyID); 
		_radius = 0;
		frames = 0;
	}
}

void GyrussEnemy::updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets, float clock){
	if(!_isDead){
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		
	switch(_enemyType){
		case EnemyType::ships:
			lemniscate(1000);
			break;
		case EnemyType::satellites:
			ArchimedesSpiral(1000);
			break;
		case EnemyType::laser:
			moveOutwards(1000, 1.0f);
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
		cout << "default" << endl;
			break;
	} 
		if(_enemyType == EnemyType::ships){
			//if(clockE.getElapsedTime().asSeconds() > 1.0f){
				_enemyWeapon.enemyShoot(*this, "enemyBullet");
				//clockE.restart();
			//}
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



void GyrussEnemy::enemySetup(sf::Texture texture){
	EnemyTexture = texture;
	EnemySprite.setTexture(EnemyTexture);
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
			_enemyCollider.setTag("ship");
			break;
		case EnemyType::satellites:
			_enemyCollider.setTag("satellite");
			break;
		case EnemyType::laser:
			_enemyCollider.setTag("laser");
			break;
		case EnemyType::generator:
			_enemyCollider.setTag("generator");
			break;
		case EnemyType::asteroids:
			_dTheta = randomAngle(_EnemyID);
			_radius = 0;
			_enemyCollider.setTag("asteroid");
			break;
		default:
			break;
	} 
	
	//allEnemies.push_back(*this);
}


float calcAngle(float yDiff, float xDiff){
	
	float angle = atan(yDiff/(xDiff+ 0.00001f));
	
	if(yDiff >= 0 && xDiff >= 0){ //first quadrant
		angle -= 4*atan(1)/2;
	} else if (yDiff >= 0 && xDiff < 0){ //second quadrant
		angle -= 4*atan(1)/2;
	} else if (yDiff < 0 && xDiff < 0){ //third quadrant
		angle += 4*atan(1)/2;
	}else if (yDiff < 0 && xDiff >= 0){ //fourth quadrant
		angle += 4*atan(1)/2;
	}
	
	return angle;
}


void GyrussEnemy::converging(float scaleFactor, float convergingRad, float clock) 
{
	
	if(_radius > convergingRad && frames < 260){
		moveOutwards(scaleFactor, -0.1f);
	}else{
		if(frames < 260){
			frames++;
			moveCircular(scaleFactor, convergingRad);
		} else {
			moveOutwards(scaleFactor, 1.0f);
		}
	}
}




void GyrussEnemy::lemniscate(float scaleFactor) 

{
	
     
	
		_dTheta  += (0.003 * 2* 1 )/1   ;
		int a = 200;
		double TempCos =    fabs(cos(1 *_dTheta)) ;  		
		
		_x =  cos(_dTheta)*sqrt( pow(a,2) *   TempCos)    +_xRefPoint  ;
		_y = sin(_dTheta)*sqrt( pow(a,2) *     TempCos )   +  _yRefPoint; 	
		
		EnemySprite.setPosition(_x, _y ) ;
		
		_radius = sqrt(  pow(  cos(_dTheta)*sqrt( pow(a,2) * TempCos)   ,2) + pow( sin(_dTheta)*sqrt( pow(a,2) *     TempCos )   ,2)    ); 
		
		EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
		cout << _radius << endl ;
		
		// _RadFromCentre   = sqrt( pow(_x- _xRefPoint   ,2 ) + pow(_y- _yRefPoint,2)); 
		 

		
	
	
}

void GyrussEnemy::ArchimedesSpiral(float scaleFactor) 
{
	
	_dTheta  += 0.05    ;
	_radius =  300 - (_dTheta*18)*2   ;
	
	if(_radius >= 0 )
	{
	_x = _radius*cos(_dTheta) + _xRefPoint  ; 
	_y = _radius*sin(_dTheta) +    _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
	
	} 
	cout << _x<<" " << _y <<" " << _radius <<endl;
	
	
}


void GyrussEnemy::Limacons(float scaleFactor) 
{
	int a = 40 , b = 80 ;  
	_dTheta +=0.005f ; 
	_x = (a + b*sin(_dTheta))*cos(_dTheta)+_xRefPoint ;
	_y = (a + b*sin(_dTheta))*sin(_dTheta)+ _yRefPoint;
	_radius = sqrt((_x - _xRefPoint)*(_x - _xRefPoint) + (_y - _yRefPoint)*(_y - _yRefPoint));
	cout << "theta " << _dTheta << endl;
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(abs(_radius)/scaleFactor, abs(_radius)/scaleFactor);
}

