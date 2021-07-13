#pragma once

namespace gn {
	class System {
	public:
		virtual void Startup() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};
}