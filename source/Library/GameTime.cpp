#include "pch.h"
#include "GameTime.h"

namespace Library
{
	GameTime::GameTime()
		: mTotalGameTime(std::chrono::milliseconds(0)), mElapsedGameTime(std::chrono::milliseconds(0))
	{
	}

	const std::chrono::high_resolution_clock::time_point& GameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const std::chrono::milliseconds& GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const std::chrono::milliseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const std::chrono::milliseconds& GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}

	bool GameTime::operator==(const GameTime& rhs) const
	{
		return (mElapsedGameTime == rhs.mElapsedGameTime && mTotalGameTime == rhs.mTotalGameTime);
	}

	bool GameTime::operator!=(const GameTime& rhs) const
	{
		return !(operator==(rhs));
	}
}