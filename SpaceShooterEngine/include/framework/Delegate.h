#pragma once

namespace ss {

	template<typename... Args>
	class Delegate {

	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::* callback)(Args...))
		{
		}
	};
}