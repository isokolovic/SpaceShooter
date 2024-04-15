#pragma once

namespace ss {

	class Object {

	public:
		Object();
		virtual ~Object();

		void Destroy();
		bool IsPendingDestroy() const { return mIsPendingDestroy; }

	private:
		bool mIsPendingDestroy; // Pending: will be destroyed in the next loop 
	};
}