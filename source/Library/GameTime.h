#pragma once
#include <chrono>

namespace Library
{
	class GameTime
	{
	public:
		GameTime();

		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);
		
		const std::chrono::milliseconds& TotalGameTime() const;
		void SetTotalGameTime(const std::chrono::milliseconds& totalGameTime);

		const std::chrono::milliseconds& ElapsedGameTime() const;
		void SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime);

		bool operator==(const GameTime& rhs) const;
		bool operator!=(const GameTime& rhs) const;
	private:
		std::chrono::milliseconds mTotalGameTime;
		std::chrono::milliseconds mElapsedGameTime;
		std::chrono::high_resolution_clock::time_point mCurrentTime;
	};
}
