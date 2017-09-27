#include "GyrussEnemy.h"


void GyrussEnemy::move(float clock){
	switch(_enemyType){
			case EnemyType::ships:
				if(clock > 10.0f ){
					converging(9.0f);
				} else{
					lemniscate(20.0f);
				}
				break;
			case EnemyType::satellites:
				if( clock > 13.0f){
					converging(9.0f);
				} else{
					if(clock > 0 && clock < 6.0f)
						ArchimedesSpiral(50.0f);
					else if( clock > 6.0f && clock < 13.0f)
						ArchimedesSpiral(-0.5f);
				}
				break;
			case EnemyType::laser:
				moveOutwards(5.0f, clock);
				break;
			case EnemyType::generator:
				if(_dTheta > 6.28f){
					converging(9.0f);
				} else{
					Limacons();
				}
				break;
			case EnemyType::asteroids:
				moveOutwards(1.0f,clock);
				break;
			default:
				break;
	}
}
void GyrussEnemy::enemyUpdate(deque<Bullet>& playerBullets, float clock){
	if(!_isDead){
		move(clock);
		if(_enemyType == EnemyType::ships){
			
			if(frames%(rand()%200+1) == 1){
				shoot(_radius, _dTheta, "enemyBullet");
			}
		}
		if(!(_enemyType == EnemyType::asteroids || _enemyType == EnemyType::laser)){
			if(isCollided() && !_isDead){
				setCollisionStatus(false);
			}
			for(auto& bullet:playerBullets){
				if(collided(bullet.getCollider())){
					if(bullet.isCollided()){
						continue;
					}
					bullet.setCollisionStatus(true);
					if(bullet.getTag() == "playerBullet"){
						playerBullets.pop_front();
						_isDead = true;
						break;
					}
				}
			}
		} else {
			setCollisionStatus(false);
		}
	}
	weaponUpdate(1.0f);
}


GyrussEnemy::GyrussEnemy(float xRef, float yRef, float angle,EnemyType enemyType, int time)
{
		frames = 0;
		_isDead = false;
		convergingTime = time;
		_enemyType = enemyType;
		_yRefPoint = yRef;
		_xRefPoint = yRef;
		_dTheta = angle;
		_x = 0;
		_y = 0;
		_radius = 0;
		setCollisionStatus(false);
	switch(enemyType){
		case EnemyType::ships:
			setTag("ship");
			break;
		case EnemyType::satellites:
			setTag("satellite");
			break;
		case EnemyType::laser:
			setTag("laser");
			break;
		case EnemyType::generator:
			setTag("generator");
			break;
		case EnemyType::asteroids:
			setTag("asteroid");
			break;
		default:
			break;
	} 
	
}

void GyrussEnemy::converging(float convergingRad) 
{
	
	if(_radius > convergingRad && frames < 600){
		moveOutwards(-5.0f, 4*atan(1));
	}else{
		if(frames < convergingTime){
			frames++;
			moveCircular(convergingRad);
		} else {
			moveOutwards(2.0f,4*atan(1));
		}
	}
}


void GyrussEnemy::lemniscate(float speed) {
	_dTheta  += (0.0005 * speed);
	int a = 200;
	double TempCos =    fabs(cos(1 *_dTheta)) ;
	_x =  cos(_dTheta)*sqrt( pow(a,2) *TempCos)    +_xRefPoint;
	_y = sin(_dTheta)*sqrt( pow(a,2) *TempCos )   +  _yRefPoint;
	_radius = sqrt(  pow(  cos(_dTheta)*sqrt( pow(a,2) * TempCos)   ,2) + pow( sin(_dTheta)*sqrt( pow(a,2)*TempCos ),2)); 
}

void GyrussEnemy::ArchimedesSpiral(float speed) 
{
	
	_dTheta  += 0.1f;
	if(speed >= 0)
	_radius =  500 - _dTheta - speed*_dTheta/3.5f;
	if(speed < 0){
		_radius +=  speed*-1.0f;
	}

	if(_radius >= 0 )
	{
		_x = _radius*cos(_dTheta) + _xRefPoint  ; 
		_y = _radius*sin(_dTheta) +    _yRefPoint;
	}	
}


void GyrussEnemy::Limacons() {
	int a = 40 , b = 80 ;  
	_dTheta +=0.005f ; 
	_x = (a + b*sin(_dTheta))*cos(_dTheta)+_xRefPoint ;
	_y = (a + b*sin(_dTheta))*sin(_dTheta)+ _yRefPoint;
	_radius = sqrt((_x - _xRefPoint)*(_x - _xRefPoint) + (_y - _yRefPoint)*(_y - _yRefPoint));
}
void GyrussEnemy::moveCircular(float radius)
{
	_radius = radius;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	_dTheta += 0.01f;
}

void GyrussEnemy::moveOutwards(float speed, float angle){
	_radius += speed;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	if(_radius  > 1000){
		_dTheta += -1*angle;
		_radius = 0;
		frames = 0;
	}
}
