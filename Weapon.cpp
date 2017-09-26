#include "Weapon.h"
#include "Player.h"
#include "GyrussEnemy.h"

Weapon::Weapon():Bullet{200, 5, "bullet"}
{
	_bulletTexture.loadFromFile("textures/enemyBullet.png");
	_bulletPrefab.setTexture(_bulletTexture);
	_bulletPrefab.setScale(0.075f,0.075f);
}

Weapon::~Weapon()
{
}

void Weapon::playerShoot(float radius, float angle, string name){
	//spawns bullet and stores it in array
	Bullet bulletSpawn(radius, angle,name);
		
	_allBullets.push_back(bulletSpawn);
}
void Weapon::enemyShoot(GyrussEnemy& enemyObject, string name){
	//spawns bullet and stores it in array
	//Bullet bulletSpawn(_bulletPrefab, enemyObject.getEnemyPosition(), enemyObject.getEnemyRotation(),enemyObject.getEnemyRadius(),name);
	//bulletSpawn.angle = enemyObject.getEnemyAngle();
	//_allBullets.push_back(bulletSpawn);
}

void Weapon::weaponUpdate(sf::RenderWindow& window, sf::Vector2f refPoint, float bulletDir){
	///for each bullet object move it 
	for(auto j = 0; j < _allBullets.size() ; j++){
		_allBullets.at(j).moveBullet(8.0f*bulletDir);
		_allBullets.at(j).bulletUpdate(refPoint, _bulletPrefab);
		window.draw(_bulletPrefab);
		//if(_allBullets.at(j).radius < 0 || _allBullets.at(j).radius > 500){
			//delete _allBullets.at(j).bulletCollider;
			//_allBullets.pop_front();			
		//}
	}
}
