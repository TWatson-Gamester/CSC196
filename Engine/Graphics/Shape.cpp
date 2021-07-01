#include "Shape.h"

namespace gn {

	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale){
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = ((points[i] * scale) + position) + gn::Vector2{ rand() % 10, rand() % 10 };
			Vector2 p2 = ((points[i + 1] * scale) + position) + gn::Vector2{ rand() % 10, rand() % 10 };
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}

}

