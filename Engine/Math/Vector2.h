#pragma once

namespace gn {
	struct Vector2 {
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

		Vector2 operator + (const Vector2& v) const { return { x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return { x - v.x, y - v.y }; }

		Vector2 operator * (float scale) const { return { x * scale, y * scale }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }

		Vector2& operator *= (float scale) { x *= scale; y *= scale; return *this; }

	};
}