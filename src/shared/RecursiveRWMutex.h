#pragma once
#include <ace/RW_Mutex.h>
#include <ace/Mutex.h>

namespace ACE_Based
{
	class RecursiveRWMutex
	{
	public:
		RecursiveRWMutex();
		void acquire_read();
		void acquire_write();

		void release_read();
		void release_write();
	private:

		ACE_RW_Mutex _backend;

		ACE_Mutex ReadCounterProtecter;
		int ReadCounter;
	};
}