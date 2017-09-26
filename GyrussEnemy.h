#ifndef GYRUSSENEMY_H
#define GYRUSSENEMY_H
#include <SFML/System.hpp>
#include <cmath>
#include <deque>
#include "Weapon.h"
#include "Collider.h"
#include <time.h>
#include <iostream>

using namespace std;
enum class EnemyType{
	ships = 0, satellites, asteroids, laser, generator
};

class GyrussEnemy
{
public:
	GyrussEnemy();
	GyrussEnemy(sf::Vector2f initPos , sf::Vector2f refPoint , sf::Sprite& enemyObject,EnemyType enemyType, int time = 600);
	void enemySetup(sf::Texture texture);
	sf::Vector2f getEnemyPosition(){return EnemySprite.getPosition();}
	float getEnemyRotation(){return EnemySprite.getRotation();}
	float getEnemyRadius(){ return _radius;}
	float getEnemyAngle(){return _dTheta;}
	deque<Bullet>& getEnemyBullets(){return _enemyWeapon.getBullets();}
	bool isEnemyDead(){return _isDead;}
	void getEnemyID(const int EnemyID ){_EnemyID = EnemyID;} ; 
	void moveCircular(float scaleFactor, float radius) ; 
	void moveOutwards(float scaleFactor, float speed);
	void lemniscate(float scaleFactor, float speed) ;
	void converging(float scaleFactor ,float convergingRad, float clock) ; //not working properly
	void ArchimedesSpiral(float scaleFactor, float speed);
	void Limacons(float scaleFactor)  ;
	
	void updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets, float clock);
	int getX() {return _x ; }
	int getY() {return _y ; }   
	
	
	~GyrussEnemy(){}
	
private:
		sf::Texture EnemyTexture ; 		
		sf::Sprite  EnemySprite ; 
		int length; 
		int width; 
		float _radius,_centreRadius;
		float _dTheta,_xscale,_yscale;
		int _Maxenemy;
		int _EnemyID , frames,convergingTime ; 
		float _x, _y,  _dx , _dy , _xRefPoint, _yRefPoint;
		bool _isDead;
		EnemyType _enemyType;
		Weapon _enemyWeapon;
		Collider _enemyCollider;
};

#endif // GYRUSSENEMY_H
