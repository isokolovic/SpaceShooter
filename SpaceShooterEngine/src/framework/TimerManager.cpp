#include "framework/TimerManager.h"

namespace ss
{
	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: mListener{ weakRef, callback },
		mDuration{ duration },
		mRepeat{ repeat },
		mTimerCounter{ 0 },
		mIsExpired{ false }
	{
	}

	void Timer::TickTimer(float deltaTime)
	{
		if (Expired()) return;

		mTimerCounter += deltaTime;
		if (mTimerCounter >= mDuration)
		{
			mListener.second();

			if (mRepeat)
			{
				mTimerCounter = 0.f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	unique<TimerManager> TimerManager::timerManager{ nullptr };

	TimerManager::TimerManager()
		: mTimers{}
	{
	}

	TimerManager& TimerManager::Get()
	{
		if (!timerManager)
		{
			timerManager = std::move(unique<TimerManager>(new TimerManager{}));
		}

		return *timerManager;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (Timer& timer : mTimers)
		{
			timer.TickTimer(deltaTime);
		}
	}
}