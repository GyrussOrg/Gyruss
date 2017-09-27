#include "Weapon.h"
#include "Player.h"
#include "GyrussEnemy.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::shoot(float radius, float angle, string name){
	//spawns bullet and stores it in array
	Bullet bulletSpawn(radius, angle,name);
	_allBullets.push_back(bulletSpawn);
}

void Weapon::weaponUpdate(float bulletDir){
	///for each bullet object move it 
	for(auto j = 0; j < _allBullets.size() ; j++){
		_allBullets.at(j).moveBullet(8.0f*bulletDir);
		_allBullets.at(j).bulletUpdate(250,250);
		if(_allBullets.at(j).getRadius() < 0 || _allBullets.at(j).getRadius() > 360){
			_allBullets.pop_front();	
		}
	}
}
