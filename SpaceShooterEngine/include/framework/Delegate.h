#pragma once
#include <functional>
#include "framework/Core.h"

namespace ss
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::* callback)(Args...))
		{
			std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool
				{
					if (!obj.expired())
					{
						(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
						return true;
					}

					return false;
				};

			mCallbacks.push_back(callbackFunc);
		}

		void Broadcast(Args... args)
		{
			for (auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
			{
				//If callback has failed (obj.expired()), remove it from callbacks
				if ((*iter)(args...))
				{
					++iter;
				}
				else
				{
					iter = mCallbacks.erase(iter);
				}
			}
		}


	private:
		List<std::function<bool(Args...)>> mCallbacks;
	};
}