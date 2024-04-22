#include "framework/Object.h"
#include "framework/Core.h"

namespace ss
{
	ss::Object::Object()
		:mIsPendingDestroy{ false }
	{
	}

	Object::~Object()
	{
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}
}
