/**	@file GameException.h
*	Contains declaration for GameException
*/
#pragma once

#include <exception>
#include <Windows.h>
#include <string>

namespace Library
{
	/**	@class GameException
	*	Class to wrap the result returned by DirectX as an exception for better error handling
	*/
	class GameException : public std::exception
	{
	public:
		/** Overloaded constructor that takes in the error message and error code */
		GameException(const char* const& message, HRESULT hr = S_OK);

		HRESULT HR() const;
		std::wstring whatw() const;

	private:
		HRESULT mHR;
	};

	inline void ThrowIfFailed(HRESULT hr, const char* const& message = "")
	{
		if (FAILED(hr))
		{
			throw GameException(message, hr);
		}
	}
}
