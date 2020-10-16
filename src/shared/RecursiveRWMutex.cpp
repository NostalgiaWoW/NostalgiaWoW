//Giperion January 2018
//[EUREKA] 3.6

#include "Common.h"
#include "RecursiveRWMutex.h"


ACE_Based::RecursiveRWMutex::RecursiveRWMutex()
	: ReadCounter(0)
{}

void ACE_Based::RecursiveRWMutex::acquire_read()
{
	ACE_Guard<ACE_Mutex> guard(ReadCounterProtecter);
	++ReadCounter;
	if (ReadCounter == 1)
	{
		_backend.acquire_read();
	}
}

void ACE_Based::RecursiveRWMutex::acquire_write()
{
	_backend.acquire_write();
}

void ACE_Based::RecursiveRWMutex::release_read()
{
	ACE_Guard<ACE_Mutex> guard(ReadCounterProtecter);
	--ReadCounter;
	if (ReadCounter < 1)
	{
		_backend.release();
	}
}

void ACE_Based::RecursiveRWMutex::release_write()
{
	_backend.release();
}
