#include "Transform.h"

namespace gn {
	void Transform::Update() {
		
		Matrix22 mxs;
		mxs.Scale(scale);

		Matrix22 mxr;
		mxr.Rotate(rotation);

		matrix = mxs * mxr;
	}
}