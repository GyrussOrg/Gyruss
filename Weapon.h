#ifndef WEAPON_H
#define WEAPON_H
#include <vector>
#include <deque>
#include <cmath>
#include "Bullet.h"
#include <iostream>
using namespace std;
class GyrussEnemy;


class Weapon
{
public:
	Weapon();
	void shoot(float radius, float angle, string name);
	void weaponUpdate(float bulletDir);
	float getMagazineSize(){return _allBullets.size();}
	deque<Bullet>& getBullets(){return _allBullets;}
	~Weapon();
private:
	deque<Bullet> _allBullets;
};

#endif // WEAPON_H
