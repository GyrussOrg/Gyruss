#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Collider
{
public:
	Collider();
	Collider(sf::FloatRect parentBounds);
	bool collided(Collider gameObject);
	void setCollisionStatus(bool iscollided){_isCollided = iscollided;}
	bool isCollided()const {return _isCollided;}
	sf::FloatRect getColliderBounds()const{return _2Dcollider;}
	Collider& getCollider(){return *this;}
	string getTag()const{return _tag;}
	void setTag(string name){_tag = name;}
	void colliderUpdate(sf::FloatRect parentBounds);
	~Collider();
private:
	sf::FloatRect _2Dcollider;
	string _tag;
	bool _isCollided;
};

#endif // COLLIDER_H
