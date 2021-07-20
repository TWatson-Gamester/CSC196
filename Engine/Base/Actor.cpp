#include "Actor.h"
#include "Graphics/Shape.h"

namespace gn {

	void Actor::Draw(Core::Graphics& graphics){
		shape->Draw(graphics, transform);
	}
}