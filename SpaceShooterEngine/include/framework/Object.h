#pragma once
#include <memory>
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ss
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return mIsPendingDestroy; }

		//For Objects to be able to provide weak reference of themselves
		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;

		Delegate<Object*> onDestroy;
		unsigned int GetUniqueID() const { return mUniqueID; }
	private:
		bool mIsPendingDestroy; //Pending: will be destroyed in the next loop 

		unsigned int mUniqueID;
		static unsigned int uniqueIDCounter;
		static unsigned int GetNextAvailableID();
	};
}