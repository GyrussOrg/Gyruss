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
	
}


void GyrussEnemy::moveCircular()
{
	_radius = 100;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
		_dTheta += 0.05f;
}

 float GyrussEnemy::randomAngle(int EnemyID){
	srand(time(0));
	int temp1 = (rand()%13 + 1);
	float Temp =  8.0*atan(1.0)/temp1 ;
	
	cout  << EnemyID  <<"   rand number: "<< temp1 <<endl; 
	return  Temp* EnemyID ;
}
void GyrussEnemy::moveOutwards(){
	_radius += 0.6f;
	_dTheta = _dTheta ;
	cout << "ID " << _EnemyID  << " anNGle  5" << _dTheta  <<endl; 
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint; 
	
	EnemySprite.setPosition(_x, _y ) ;
	EnemySprite.setScale(_radius/300, _radius/300);
	if(_radius  > 500){
		_dTheta += -1*randomAngle(_EnemyID); 
		_radius = 0;
	}
}

void GyrussEnemy::updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets){
	if(!_isDead){
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		
	moveOutwards() ; 
	//lemniscate(); 
	 //converging() ;
	// ArchimedesSpiral();
	 //Limacons()  ;
		
		if(clockE.getElapsedTime().asSeconds() > 1.0f){
			_enemyWeapon.enemyShoot(*this, "enemyBullet");
			clockE.restart();
		}
		_enemyWeapon.weaponUpdate(window,sf::Vector2<float> (250,250), 1.0f);
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
	
		_centreRadius   = 15 ; 
		_xscale = EnemySprite.getScale().x ;
		_yscale = EnemySprite.getScale().y ;

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
			_dTheta = randomAngle(_EnemyID);
			_radius = 0;
			_enemyCollider.setTag("asteroid");
			break;
		default:
			break;
	} 
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


void GyrussEnemy::converging() 
{

	// if( _radius  > _centreRadius )
	 //{
	 _dTheta = 0 ; 
		_radius -= 1 ; 
		 _x= _radius *cos(_dTheta)  +_xRefPoint ; 
		_y = _radius*sin(_dTheta) + _yRefPoint ;
		EnemySprite.setPosition(_x, _y ) ;
		cout << "asdedde x :   " << _radius << "    y:  "<< _y <<endl ;
		
		//if( (_radius)  > _centreRadius*4   )
		//{
			//EnemySprite.setScale(  _xscale  * (_radius/200)   ,   _yscale * (_radius/200) );
		//}	 

	//}
}




void GyrussEnemy::lemniscate() 

{
	
     
	
		_dTheta  += (0.01 * 2* 1 )/1   ;
		int a = 200;
		double TempCos =    fabs(cos(1 *_dTheta)) ;  		
		
		_x =  cos(_dTheta)*sqrt( pow(a,2) *   TempCos)    +_xRefPoint  ;
		_y = sin(_dTheta)*sqrt( pow(a,2) *     TempCos )   +  _yRefPoint; 	
		
		EnemySprite.setPosition(_x, _y ) ;
		
		
		
		// _RadFromCentre   = sqrt( pow(_x- _xRefPoint   ,2 ) + pow(_y- _yRefPoint,2)); 
		 

		
	
	
}

void GyrussEnemy::ArchimedesSpiral() 
{
	
	_dTheta  += 0.05    ;
	_radius =  300 - (_dTheta*18)*2   ;
	
	if(_radius >= 0 )
	{
	_x = _radius*cos(_dTheta) + _xRefPoint  ; 
	_y = _radius*sin(_dTheta) +    _yRefPoint;
	
	}
	
	EnemySprite.setPosition(_x, _y ) ;
	

	
	
}


void GyrussEnemy::Limacons() 
{
	int a = 40 , b = 80 ;  
	_dTheta +=0.01 ; 
	_x = (a + b*sin(_dTheta))*cos(_dTheta)+_xRefPoint ;
	_y = (a + b*sin(_dTheta))*sin(_dTheta)+ _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	
	
	
}

