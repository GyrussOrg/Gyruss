#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <deque>
#include <cmath>
#include "Bullet.h"
#include <iostream>
using namespace std;
class GyrussEnemy;


class Weapon: public Bullet
{
public:
	Weapon();
	void playerShoot(float radius, float angle, string name);
	void enemyShoot(GyrussEnemy& enemy, string name);
	void weaponUpdate(sf::RenderWindow& window, sf::Vector2f, float bulletDir);
	deque<Bullet>& getBullets(){return _allBullets;}
	~Weapon();
private:
	sf::Sprite _bulletPrefab;
	sf::Texture _bulletTexture;
	deque<Bullet> _allBullets;
};

#endif // WEAPON_H
