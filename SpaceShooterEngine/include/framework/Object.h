#pragma once
#include <memory>
#include "framework/Core.h"

namespace ss {

	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return mIsPendingDestroy; }

		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;
	private:
		bool mIsPendingDestroy; // Pending: will be destroyed in the next loop 
	};
}