#include "Player.h"
#include "GyrussEnemy.h"
#include "Collider.h"
#include "Weapon.h"
#include "Bullet.h"
#include <time.h>
#include <deque>
#include <SFML/System.hpp>
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


//Player tests
TEST_CASE("Test player initial position")
{
	Player player(250,250,200);
	float xinitial =250 , yinitial = 450;
	CHECK(player.getX() == xinitial);
	CHECK(player.getY() == yinitial);
}

TEST_CASE("Test player move right")
{
	Player player(250,250,200);
	float xDestination = 450;
	float yDestination = 250;
	auto tolerance = 0.1f ;
	
	while(!(((player.getX() > xDestination - tolerance)&& (player.getX() < xDestination + tolerance))
		 && (player.getY() > yDestination - tolerance)&& (player.getY() < yDestination + tolerance)))
	{
		player.move(-7.0f);
	}
	
	CHECK((fabs(player.getX() - xDestination) <= tolerance));
	CHECK((fabs(player.getY() - yDestination) <= tolerance));
}

TEST_CASE("Test player move left")
{
	Player player(250,250,200);
	float xDestination = 250;
	float yDestination = 50;
	auto tolerance = 0.1f ;
	
	while(!(((player.getX() > xDestination - tolerance)&& (player.getX() < xDestination + tolerance))
		 && (player.getY() > yDestination - tolerance)&& (player.getY() < yDestination + tolerance)))
	{
		player.move(7.0f);
	}
	
	CHECK((fabs(player.getX() - xDestination) <= tolerance));
	CHECK((fabs(player.getY() - yDestination) <= tolerance));
}

TEST_CASE("Test player radius is constant")
{
	Player player(250,250,200);
	auto tempRadius = 200.0f;
	auto initialAngle = player.getAngle();
	bool radiusChange = false ;
	
	while(1)
	{
		player.move(7.0f);
		
		if( ! (player.getRadius() == tempRadius ))
		{
			radiusChange = true;
		}
		
		if(player.getAngle() > initialAngle - 2*atan(1))
			break;
	}
	
	CHECK_FALSE(radiusChange);
}
///Collider Tests
TEST_CASE("test for collission"){
	Collider collider1(sf::Rect<float> (20,5,25,25));
	Collider collider2(sf::Rect<float> (20,5,25,25));
	
	CHECK(collider1.collided(collider2));
}

///Bullet tests
TEST_CASE("Check if bullet moves"){
	Bullet bullet(500,0, "testBullet");
	float xReference = 250.0f;
	float yReference = 250.0f;
	float tolerance = 0.1f;
	while(1){
		bullet.moveBullet(-10.0f);
		bullet.bulletUpdate(xReference,yReference);
		if( (fabs(bullet.getXpos() - xReference) < tolerance) && (fabs(bullet.getYpos() - yReference) < tolerance)){
			break;
		}
	}
	
	CHECK((fabs(bullet.getXpos() - xReference) <= tolerance));
	CHECK(fabs(bullet.getYpos() - yReference) <= tolerance);
}


//Weapon
TEST_CASE("test if multiple bullet are spawned when shooting"){
	Weapon weapon;
	CHECK(weapon.getMagazineSize() == 0);
	weapon.shoot(200,0,"bullet");
	CHECK(weapon.getMagazineSize() == 1);
	weapon.shoot(20, 3.142, "bullet");
	CHECK(weapon.getMagazineSize() == 2);
}

TEST_CASE("test if bullet is deleted at the center and out of screen"){
	Weapon weapon1;
	Weapon weapon2;
	auto loops = 0;
	weapon1.shoot(200,0,"bullet1");
	weapon2.shoot(0,0,"bullet2");
	while(1){
		if(weapon1.getMagazineSize() == 0 && weapon2.getMagazineSize() == 0){
			break;
		}
		weapon1.weaponUpdate(-1.0f);
		weapon2.weaponUpdate(1.0f);
		loops++;
	}
	
	CHECK(loops > 0);
	CHECK(weapon1.getMagazineSize() == 0);
	CHECK(weapon2.getMagazineSize() == 0);
}
//Enemy test
TEST_CASE("test if enemy moves and goes to center"){
	GyrussEnemy enemy(250,250,3.142,EnemyType::ships,1000);
	clock_t time;
	time = clock();
	cout << "please wait a moment, calculation in progress" << endl;
	while(1){
		time = clock() - time;
		enemy.move((float)time/CLOCKS_PER_SEC);
		if((float)time/CLOCKS_PER_SEC > 13.5f)
			break;
	}
	
	CHECK(enemy.getEnemyRadius() < 10.0f);
}

TEST_CASE("test if player can shoot"){
	Player player(250,250,200);
	GyrussEnemy enemy(250,250,3.142);
	deque<Bullet> bullets;
	player.playerShoot();
	while(1){
		player.playerUpdate(bullets,enemy,0);
		enemy.enemyUpdate(player.getBullets(),0);
		if(player.getMagazineSize() == 0){
			break;
		}
	}
		
	CHECK(enemy.isEnemyDead());
}