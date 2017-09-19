#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include <SFML/Graphics.hpp>

class SpriteHandler{
	public:
		virtual void move() = 0;
		sf::Vector2f getPosition( const sf::Sprite& gameObject){
			return gameObject.getPosition();
		}
		virtual float getElapsedTime(sf::Clock clock);
		virtual float getAngle() = 0;
		virtual void shoot()= 0;
		virtual void setTexture(string& path) = 0;
};


#endif