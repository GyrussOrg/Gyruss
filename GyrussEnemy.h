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

class GyrussEnemy: public Weapon, public Collider
{
public:
	GyrussEnemy(float xRef, float yRef, float angle,EnemyType enemyType = EnemyType::ships, int time = 600);
	float getEnemyRadius(){ return _radius;}
	float getEnemyAngle(){return _dTheta;}
	bool isEnemyDead(){return _isDead;}
	void moveCircular(float radius); 
	void moveOutwards(float speed, float angle);
	void lemniscate(float speed);
	void converging(float convergingRad);
	void ArchimedesSpiral(float speed);
	void Limacons();
	void enemyUpdate(deque<Bullet>& playerBullets, float clock);
	void move(float clock);
	int getX() {return _x ;}
	int getY() {return _y ;}   
	
	
	~GyrussEnemy(){}
	
private:
		float _radius;
		float _dTheta;
		int frames,convergingTime ; 
		float _x, _y, _xRefPoint, _yRefPoint;
		bool _isDead;
		EnemyType _enemyType;
};

#endif // GYRUSSENEMY_H
