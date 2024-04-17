#include "framework/Object.h"
#include "framework/Core.h"

namespace ss {

	ss::Object::Object()
		:mIsPendingDestroy{ false }
	{
	}

	Object::~Object()
	{
		LOG("Object destroyed! ");
	}

	void Object::Destroy()
	{
		mIsPendingDestroy = true;
	}
}
