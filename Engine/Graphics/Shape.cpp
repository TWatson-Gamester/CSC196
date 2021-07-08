#include "Shape.h"

namespace gn {

	void Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale){
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = ((Vector2::Rotate(points[i], angle) * scale) + position);
			Vector2 p2 = ((Vector2::Rotate(points[i + 1], angle) * scale) + position);
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform) {
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = (Vector2::Rotate(points[i], transform.rotation) * transform.scale);
			Vector2 p2 = (Vector2::Rotate(points[i+1], transform.rotation) * transform.scale);
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}
}

