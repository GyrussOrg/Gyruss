#include "Collider.h"

Collider::Collider():
_2Dcollider{sf::Rect<float> (600,600,2,3)},_tag{"noNAme"}, _isCollided{false}
{
	
}

Collider::Collider(sf::FloatRect& parentBounds):
_2Dcollider{parentBounds}, _tag{"noNAme"}, _isCollided{false}
{
	
}

Collider::~Collider()
{	
}


void Collider::colliderUpdate(sf::FloatRect parentBounds){
	_2Dcollider = parentBounds;
}


bool  Collider::collided(Collider& gameObject){
	if(_isCollided){
		return false;
	}
	if(_2Dcollider.intersects(gameObject.getColliderBounds())){
		_isCollided = true;
	}
	return _isCollided;
}

