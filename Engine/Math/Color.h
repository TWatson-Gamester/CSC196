#pragma once
#include "core.h"

namespace gn {
	struct Color {
		float r, g, b;

		Color() : r{0}, g{0}, b{0} {}
		Color(float r, float g, float b) : r{r}, g{g}, b{b} {}
		Color(DWORD rgb) //DWORD( x | b | g | r )
		{
			r = (rgb & 0xFF) / 255.0f;			// 0 - 255 -> 0 - 1
			g = ((rgb >> 8) & 0xFF) / 255.0f;	// 0 - 255 -> 0 - 1
			b = ((rgb >> 16) & 0xFF) / 255.0f;	// 0 - 255 -> 0 - 1
		}

		Color operator + (const Color color) { return {r + color.r, g + color.g, b + color.b}; }
		Color operator - (const Color color) { return {r - color.r, g - color.g, b - color.b}; }

		Color operator * (float scale) const { return { r * scale, g * scale, b * scale }; }

		operator DWORD() const { return ToRGB(); }
		

		DWORD ToRGB() const {
			BYTE red = static_cast<BYTE>(r * 255);
			BYTE green = static_cast<BYTE>(g * 255);
			BYTE blue = static_cast<BYTE>(b * 255);

			return (red | (green << 8) | (blue << 16));
		}

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color purple;
		static const Color cyan;
		static const Color orange;
		static const Color black;
		static const Color yellow;

	};
}